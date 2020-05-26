#include <stdlib.h>
#include <ncurses.h>
#include "string.h"

#include "dungeon.h"
#include "pc.h"
#include "utils.h"
#include "move.h"
#include "path.h"

void pc_delete(pc_t *pc)
{
  if (pc)
  {
    free(pc);
  }
}

uint32_t pc_is_alive(dungeon_t *d)
{
  return d->pc.alive;
}

void place_pc(dungeon_t *d)
{
  d->pc.position[dim_y] = rand_range(d->rooms->position[dim_y],
                                     (d->rooms->position[dim_y] +
                                      d->rooms->size[dim_y] - 1));
  d->pc.position[dim_x] = rand_range(d->rooms->position[dim_x],
                                     (d->rooms->position[dim_x] +
                                      d->rooms->size[dim_x] - 1));
}

void config_pc(dungeon_t *d)
{
  memset(&d->pc, 0, sizeof(d->pc));
  d->pc.symbol = '@';

  place_pc(d);

  d->pc.speed = PC_SPEED;
  d->pc.alive = 1;
  d->pc.sequence_number = 0;
  d->pc.pc = calloc(1, sizeof(*d->pc.pc));
  d->pc.npc = NULL;
  d->pc.kills[kill_direct] = d->pc.kills[kill_avenged] = 0;

  d->character[d->pc.position[dim_y]][d->pc.position[dim_x]] = &d->pc;

  dijkstra(d);
  dijkstra_tunnel(d);
}

uint32_t pc_next_pos(dungeon_t *d, pair_t dir)
{
  dir[dim_y] = dir[dim_x] = 0;
  int ch;
  ch = getchar();
  if (ch == '7' || ch == 'y')
  {
    //printf("7");
    dir[dim_y] = -1;
    dir[dim_x] = -1;
    return 0;
  }
  else if (ch == '8' || ch == 'k')
  {
    dir[dim_y] = -1;
    //printf("8");
    return 0;
  }
  else if (ch == '9' || ch == 'u')
  {
    dir[dim_y] = -1;
    dir[dim_x] = 1;
    //printf("9");
    return 0;
  }
  else if (ch == '6' || ch == 'l')
  {
    dir[dim_x] = 1;
    //printf("6");
    return 0;
  }
  else if (ch == '3' || ch == 'n')
  {
    dir[dim_x] = 1;
    dir[dim_y] = 1;
    //printf("3");
    return 0;
  }
  else if (ch == '2' || ch == 'j')
  {
    dir[dim_y] = 1;
    //printf("2");
    return 0;
  }
  else if (ch == '4' || ch == 'h')
  {
    dir[dim_x] = -1;
    //printf("4");
    return 0;
  }
  else if (ch == '<')
  {
    //printf("<");
    return 2;
  }
  else if (ch == '>')
  {
    //printf(">");
    return 3;
  }
  else if (ch == '5' || ch == ' ')
  {
    //printf("5");
    return 0;
  }
  else if (ch == 'm')
  {
    display_monsters(d);
    //printf("m");
    return 0;
  }
  else if (ch == 'Q')
  {
    //printf("Q");
    return -1;
  }
  else if (ch == '1' || ch == 'b')
  {
    dir[dim_y] = 1;
    dir[dim_x] = -1;
    //printf("1");
    return 0;
  }
  else
  {
    //printf("BAD MOVE %c\n", ch);

    // if (in_corner(d, &d->pc)) {
    //   if (!count) {
    //     count = 1;
    //   }
    //   have_seen_corner = 1;
    // }

    // /* First, eat anybody standing next to us. */
    // if (charxy(d->pc.position[dim_x] - 1, d->pc.position[dim_y] - 1)) {
    //   dir[dim_y] = -1;
    //   dir[dim_x] = -1;
    // } else if (charxy(d->pc.position[dim_x], d->pc.position[dim_y] - 1)) {
    //   dir[dim_y] = -1;
    // } else if (charxy(d->pc.position[dim_x] + 1, d->pc.position[dim_y] - 1)) {
    //   dir[dim_y] = -1;
    //   dir[dim_x] = 1;
    // } else if (charxy(d->pc.position[dim_x] - 1, d->pc.position[dim_y])) {
    //   dir[dim_x] = -1;
    // } else if (charxy(d->pc.position[dim_x] + 1, d->pc.position[dim_y])) {
    //   dir[dim_x] = 1;
    // } else if (charxy(d->pc.position[dim_x] - 1, d->pc.position[dim_y] + 1)) {
    //   dir[dim_y] = 1;
    //   dir[dim_x] = -1;
    // } else if (charxy(d->pc.position[dim_x], d->pc.position[dim_y] + 1)) {
    //   dir[dim_y] = 1;
    // } else if (charxy(d->pc.position[dim_x] + 1, d->pc.position[dim_y] + 1)) {
    //   dir[dim_y] = 1;
    //   dir[dim_x] = 1;
    // } else if (!have_seen_corner || count < 250) {
    //   /* Head to a corner and let most of the NPCs kill each other off */
    //   if (count) {
    //     count++;
    //   }
    //   if (!against_wall(d, &d->pc) && ((rand() & 0x111) == 0x111)) {
    //     dir[dim_x] = (rand() % 3) - 1;
    //     dir[dim_y] = (rand() % 3) - 1;
    //   } else {
    //     dir_nearest_wall(d, &d->pc, dir);
    //   }
    // }else {
    //   /* And after we've been there, let's head toward the center of the map. */
    // if (!against_wall(d, &d->pc) && ((rand() & 0x111) == 0x111)) {
    //   dir[dim_x] = (rand() % 3) - 1;
    //   dir[dim_y] = (rand() % 3) - 1;
    // } else {
    //   dir[dim_x] = ((d->pc.position[dim_x] > DUNGEON_X / 2) ? -1 : 1);
    //   dir[dim_y] = ((d->pc.position[dim_y] > DUNGEON_Y / 2) ? -1 : 1);
    // }
    // }

    // /* Don't move to an unoccupied location if that places us next to a monster */
    // if (!charxy(d->pc.position[dim_x] + dir[dim_x],
    //             d->pc.position[dim_y] + dir[dim_y]) &&
    //     ((charxy(d->pc.position[dim_x] + dir[dim_x] - 1,
    //              d->pc.position[dim_y] + dir[dim_y] - 1) &&
    //       (charxy(d->pc.position[dim_x] + dir[dim_x] - 1,
    //               d->pc.position[dim_y] + dir[dim_y] - 1) != &d->pc)) ||
    //      (charxy(d->pc.position[dim_x] + dir[dim_x] - 1,
    //              d->pc.position[dim_y] + dir[dim_y]) &&
    //       (charxy(d->pc.position[dim_x] + dir[dim_x] - 1,
    //               d->pc.position[dim_y] + dir[dim_y]) != &d->pc)) ||
    //      (charxy(d->pc.position[dim_x] + dir[dim_x] - 1,
    //              d->pc.position[dim_y] + dir[dim_y] + 1) &&
    //       (charxy(d->pc.position[dim_x] + dir[dim_x] - 1,
    //               d->pc.position[dim_y] + dir[dim_y] + 1) != &d->pc)) ||
    //      (charxy(d->pc.position[dim_x] + dir[dim_x],
    //              d->pc.position[dim_y] + dir[dim_y] - 1) &&
    //       (charxy(d->pc.position[dim_x] + dir[dim_x],
    //               d->pc.position[dim_y] + dir[dim_y] - 1) != &d->pc)) ||
    //      (charxy(d->pc.position[dim_x] + dir[dim_x],
    //              d->pc.position[dim_y] + dir[dim_y] + 1) &&
    //       (charxy(d->pc.position[dim_x] + dir[dim_x],
    //               d->pc.position[dim_y] + dir[dim_y] + 1) != &d->pc)) ||
    //      (charxy(d->pc.position[dim_x] + dir[dim_x] + 1,
    //              d->pc.position[dim_y] + dir[dim_y] - 1) &&
    //       (charxy(d->pc.position[dim_x] + dir[dim_x] + 1,
    //               d->pc.position[dim_y] + dir[dim_y] - 1) != &d->pc)) ||
    //      (charxy(d->pc.position[dim_x] + dir[dim_x] + 1,
    //              d->pc.position[dim_y] + dir[dim_y]) &&
    //       (charxy(d->pc.position[dim_x] + dir[dim_x] + 1,
    //               d->pc.position[dim_y] + dir[dim_y]) != &d->pc)) ||
    //      (charxy(d->pc.position[dim_x] + dir[dim_x] + 1,
    //              d->pc.position[dim_y] + dir[dim_y] + 1) &&
    //       (charxy(d->pc.position[dim_x] + dir[dim_x] + 1,
    //               d->pc.position[dim_y] + dir[dim_y] + 1) != &d->pc)))) {
    //   dir[dim_x] = dir[dim_y] = 0;
    // }

    return 4;
  }
}

uint32_t pc_in_room(dungeon_t *d, uint32_t room)
{
  if ((room < d->num_rooms) &&
      (d->pc.position[dim_x] >= d->rooms[room].position[dim_x]) &&
      (d->pc.position[dim_x] < (d->rooms[room].position[dim_x] +
                                d->rooms[room].size[dim_x])) &&
      (d->pc.position[dim_y] >= d->rooms[room].position[dim_y]) &&
      (d->pc.position[dim_y] < (d->rooms[room].position[dim_y] +
                                d->rooms[room].size[dim_y])))
  {
    return 1;
  }

  return 0;
}
