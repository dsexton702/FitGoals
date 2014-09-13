#ifndef WORKOUT_H
#define WORKOUT_H
  
  enum {
  SPY_KEY_START,
  SPY_KEY_STOP,
  TODO_KEY_MOVE,
  TODO_KEY_TOGGLE_STATE,
  TODO_KEY_FETCH,
};
static char text_buffer[2048];
static char *text_one;
static char *text_two;
static char *text_three;
static char *text_four;
static char *text_five;
static char *text_six;
static int num;
struct NutriInfo{
  int cal;
  int car;
  int pro;
  int sug;
  int fib;
  int fat;
};

  
  void send_message(void);
void out_sent_handler(DictionaryIterator *sent, void *context);


void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context);


void in_received_handler(DictionaryIterator *received, void *context);


void in_dropped_handler(AppMessageResult reason, void *context);

 # endif