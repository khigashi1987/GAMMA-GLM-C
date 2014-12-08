CC	= gcc
CFLAGS	= -O2
SRCS	= gammaglm.c learn.c read.c write.c random.c
OBJS	= $(SRCS:.c=.o)
HEADERS	= $(SRCS:.c=.h)
LDFLAGS	= -lm
TARGET	= gammaglm
VERSION	= 0.1

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:
	@rm -f $(OBJS)
