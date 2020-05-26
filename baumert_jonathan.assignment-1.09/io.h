#ifndef IO_H
# define IO_H

class dungeon;
class object;

void io_init_terminal(void);
void io_reset_terminal(void);
void io_display(dungeon *d);
void io_handle_input(dungeon *d);
void io_queue_message(const char *format, ...);
void io_display_inventory(dungeon *d);
void io_display_equipment(dungeon *d);
void io_inspect_item(dungeon *d);
void io_inspect_monster(dungeon *d);
object * io_select_inventory(dungeon *d, int i);
object * io_select_equipment(dungeon *d, int i);
void io_pc_drop_item(dungeon *d);
void io_pc_delete_item(dungeon *d);
void io_wear_item(dungeon *d);
void io_takeoff_item(dungeon *d);
void update_pc_speed(dungeon *d);
int convert_to_int(char t, int i);
#endif
