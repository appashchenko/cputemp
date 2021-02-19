#include "../include/io.h"
#include "../include/memory.h"
#include "../include/process.h"
#include "../include/signal.h"
#include "../include/string.h"

#define TEMP_HIGHLOAD 60000
#define TEMP_MAX 70000
#define TEMP_HYST_CRIT 96000
#define TEMP_CRYT 97000

#define COLOR_COLD "#5DADE2"
#define COLOR_NORMAL "#52BE80"
#define COLOR_HILOAD "#FFC300"
#define COLOR_WARNING "#D68910"
#define COLOR_CRITICAL "#FF7373"

enum state { NORMAL, HILOAD, WARNING, CRITICAL };

static volatile int running = 1;
static int temp_input = -1;

void print(const char* text) {
  write(1, text, strlen(text));
}

void signal_handler() {
  if (temp_input) {
    close(temp_input);
  }
  running = 0;
}

int main() {
  const char* temp_input_name = "/sys/class/hwmon/hwmon5/temp1_input";
  char buffer[6] = {0};
  char output[] = "CPU<span color='#75FF75'>   . °C</span>\n\0";
  enum state last_state = NORMAL;

  /* @TODO: handle Ctrl+C
  sigaction_t act = {0}, oact = {0};
  memset(&act, 0, sizeof (sigaction_t));
  act.sa_handler = signal_handler;
  sigemptyset(&act.sa_mask);
  sigaddset(&act.sa_mask, SIGINT);
  act.sa_flags = SA_NODEFER;
  if (sigaction(SIGINT, &act, 0) < 0) {
    print("Failed to set sigaction\n");
    return 0;
  }
  sigaction(SIGINT, NULL, &oact);
  */

  temp_input = open(temp_input_name, O_RDONLY | O_NOATIME, 0);

  if (temp_input == -1) {
    print("UNK");
    return 0;
  }

  while (running) {
    unsigned int ival = 0;

    int readed = (int)read(temp_input, &buffer, 6);
    lseek(temp_input, 0, SEEK_SET);

    if (readed <= 0) {
      print("UNK");
      return 0;
    }

    ival = (unsigned int)atoi(buffer);

    if (ival >= TEMP_HIGHLOAD) {
      if (ival >= TEMP_MAX) {
        if (ival >= TEMP_HYST_CRIT) {
          if (last_state != CRITICAL) {
            memcpy(&output[16], COLOR_CRITICAL, 7);
            last_state = CRITICAL;
          }
        } else {
          if (last_state != WARNING) {
            memcpy(&output[16], COLOR_WARNING, 7);
            last_state = WARNING;
          }
        }
      } else {
        if (last_state != HILOAD) {
          memcpy(&output[16], COLOR_HILOAD, 7);
          last_state = HILOAD;
        }
      }
    } else {
      if (last_state != NORMAL) {
        memcpy(&output[16], COLOR_NORMAL, 7);
        last_state = NORMAL;
      }
    }

    //  if (readed < 2) {
    //    output[11] = 0;
    //    output[9] = 0;
    //    print(output);
    //    return 0;
    //  }
    //  199999

    if ((buffer[readed - 1] = '\n')) {
      readed = readed - 1;
    }

    if (buffer[readed - 1] >= 0x35) {
      buffer[readed - 1] = 0x30;
      buffer[readed - 2] += 1;
    }
    if (buffer[readed - 2] >= 0x35) {
      buffer[readed - 2] = 0x30;
      buffer[readed - 3] += 1;
    }

    if (buffer[readed - 3] >= 0x3a) {
      buffer[readed - 3] = 0x30;
      buffer[readed - 4] += 1;
    }
    output[29] = buffer[readed - 3];

    if (buffer[readed - 4] >= 0x3a) {
      buffer[readed - 4] = 0x30;
      buffer[readed - 5] += 1;
    }
    output[27] = buffer[readed - 4];

    if ((int)readed - 5 >= 0) {
      if (buffer[readed - 5] >= 0x3a) {
        buffer[readed - 5] = 0x30;
        if (readed - 6 >= 0) {
          buffer[readed - 6] += 1;
        } else {
          output[27] = 0x31;
        }
      }
      output[26] = buffer[readed - 5];
    }

    if ((int)readed - 6 >= 0) {
      if (buffer[readed - 6] >= 0x3a) {
        buffer[readed - 6] = 0x30;
      }
      output[25] = buffer[0];
    }

    print(output);
    sleep(1, 0);
  }

  close(temp_input);
  return 0;
}
