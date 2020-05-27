#include "move.h"

#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <ncurses.h>
#include "dungeon.h"
#include "heap.h"
#include "move.h"
#include "npc.h"
#include "pc.h"
#include "character.h"
#include "utils.h"
#include "path.h"
#include "event.h"

void do_combat(dungeon_t *d, character_t *atk, character_t *def)
{
  if (def->alive)
  {
    def->alive = 0;
    if (def != &d->pc)
    {
      d->num_monsters--;
    }
    atk->kills[kill_direct]++;
    atk->kills[kill_avenged] += (def->kills[kill_direct] +
                                 def->kills[kill_avenged]);
  }
}

void move_character(dungeon_t *d, character_t *c, pair_t next)
{
  if (charpair(next) &&
      ((next[dim_y] != c->position[dim_y]) ||
       (next[dim_x] != c->position[dim_x])))
  {
    do_combat(d, c, charpair(next));
  }
  else
  {
    /* No character in new position. */

    d->character[c->position[dim_y]][c->position[dim_x]] = NULL;
    c->position[dim_y] = next[dim_y];
    c->position[dim_x] = next[dim_x];
    d->character[c->position[dim_y]][c->position[dim_x]] = c;
  }
}

int do_moves(dungeon_t *d)
{
  pair_t next;
  character_t *c;
  event_t *e;

  char badMove[40] = "Cannot move that way, make another move!";
  char noStair[40] = "No stairs here, make another move!      ";
  /* Remove the PC when it is PC turn.  Replace on next call.  This allows *
   * use to completely uninit the heap when generating a new level without *
   * worrying about deleting the PC.                                       */

  if (pc_is_alive(d))
  {
    /* The PC always goes first one a tie, so we don't use new_event().  *
     * We generate one manually so that we can set the PC sequence       *
     * number to zero.                                                   */
    e = malloc(sizeof(*e));
    e->type = event_character_turn;
    /* Hack: New dungeons are marked.  Unmark and ensure PC goes at d->time, *
     * otherwise, monsters get a turn before the PC.                         */
    if (d->is_new)
    {
      d->is_new = 0;
      e->time = d->time;
    }
    else
    {
      e->time = d->time + (1000 / d->pc.speed);
    }
    e->sequence = 0;
    e->c = &d->pc;
    heap_insert(&d->events, e);
  }

  while (pc_is_alive(d) &&
         (e = heap_remove_min(&d->events)) &&
         ((e->type != event_character_turn) || (e->c != &d->pc)))
  {
    d->time = e->time;
    if (e->type == event_character_turn)
    {
      c = e->c;
    }
    if (!c->alive)
    {
      if (d->character[c->position[dim_y]][c->position[dim_x]] == c)
      {
        d->character[c->position[dim_y]][c->position[dim_x]] = NULL;
      }
      if (c != &d->pc)
      {
        event_delete(e);
      }
      continue;
    }

    npc_next_pos(d, c, next);
    move_character(d, c, next);

    heap_insert(&d->events, update_event(d, e, 1000 / c->speed));
  }

  if (pc_is_alive(d) && e->c == &d->pc)
  {
    int i;
    c = e->c;
    d->time = e->time;
    /* Kind of kludgey, but because the PC is never in the queue when   *
     * we are outside of this function, the PC event has to get deleted *
     * and recreated every time we leave and re-enter this function.    */
    e->c = NULL;
    event_delete(e);
    i = pc_next_pos(d, next);
    //printf("\n next pos return val:%d",i);
    if (i == -1)
    {
      return -1;
    }
    next[dim_x] += c->position[dim_x];
    next[dim_y] += c->position[dim_y];
    if (i == 2 && mappair(next) == ter_up_stair)
    {
      //printf("MOVE UP");
      clear();
      delete_dungeon(d);
      pc_delete(d->pc.pc);
      init_dungeon(d);
      gen_dungeon(d);
      config_pc(d);
      gen_monsters(d);
      render_dungeon(d);
    }
    while (i == 2 && mappair(next) != ter_up_stair)
    {
      for (i = 0; i < 40; ++i)
      {
        mvaddch(21,i,noStair[i]);
      }
      i = pc_next_pos(d, next);
      if (i == -1)
      {
        return -1;
      }
      next[dim_x] += c->position[dim_x];
      next[dim_y] += c->position[dim_y];
    }
    if (i == 3 && mappair(next) == ter_down_stair)
    {
      //printf("MOVE DOWN");
      clear();
      delete_dungeon(d);
      pc_delete(d->pc.pc);
      init_dungeon(d);
      gen_dungeon(d);
      config_pc(d);
      gen_monsters(d);
      render_dungeon(d);
    }
    while (i == 3 && mappair(next) != ter_down_stair)
    {
      for (i = 0; i < 40; ++i)
      {
        mvaddch(21,i,noStair[i]);
        refresh();
      }
      i = pc_next_pos(d, next);
      if (i == -1)
      {
        return -1;
      }
      next[dim_x] += c->position[dim_x];
      next[dim_y] += c->position[dim_y];
    }
    while (mappair(next) == ter_wall || i == 4)
    {
      for (i = 0; i < 40; ++i)
      {
        mvaddch(21,i,badMove[i]);
        refresh();
      }
      i = pc_next_pos(d, next);
      if (i == -1)
      {
        return -1;
      }
      next[dim_x] += c->position[dim_x];
      next[dim_y] += c->position[dim_y];
    }
    for (i = 0; i < 40; ++i)
    {
      mvaddch(21, i, ' ');
      refresh();
    }
    move_character(d, c, next);

    dijkstra(d);
    dijkstra_tunnel(d);
  }
  return 0;
}

void dir_nearest_wall(dungeon_t *d, character_t *c, pair_t dir)
{
  dir[dim_x] = dir[dim_y] = 0;

  if (c->position[dim_x] != 1 && c->position[dim_x] != DUNGEON_X - 2)
  {
    dir[dim_x] = (c->position[dim_x] > DUNGEON_X - c->position[dim_x] ? 1 : -1);
  }
  if (c->position[dim_y] != 1 && c->position[dim_y] != DUNGEON_Y - 2)
  {
    dir[dim_y] = (c->position[dim_y] > DUNGEON_Y - c->position[dim_y] ? 1 : -1);
  }
}

uint32_t against_wall(dungeon_t *d, character_t *c)
{
  return ((mapxy(c->position[dim_x] - 1,
                 c->position[dim_y]) == ter_wall_immutable) ||
          (mapxy(c->position[dim_x] + 1,
                 c->position[dim_y]) == ter_wall_immutable) ||
          (mapxy(c->position[dim_x],
                 c->position[dim_y] - 1) == ter_wall_immutable) ||
          (mapxy(c->position[dim_x],
                 c->position[dim_y] + 1) == ter_wall_immutable));
}

uint32_t in_corner(dungeon_t *d, character_t *c)
{
  uint32_t num_immutable;

  num_immutable = 0;

  num_immutable += (mapxy(c->position[dim_x] - 1,
                          c->position[dim_y]) == ter_wall_immutable);
  num_immutable += (mapxy(c->position[dim_x] + 1,
                          c->position[dim_y]) == ter_wall_immutable);
  num_immutable += (mapxy(c->position[dim_x],
                          c->position[dim_y] - 1) == ter_wall_immutable);
  num_immutable += (mapxy(c->position[dim_x],
                          c->position[dim_y] + 1) == ter_wall_immutable);

  return num_immutable > 1;
}

uint32_t move_pc(dungeon_t *d, uint32_t dir)
{
  return 1;
}
