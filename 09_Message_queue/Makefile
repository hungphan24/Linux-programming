CC := g++
SRC_DIR := src
INC_DIR := inc
BIN_DIR := bin

# Tất cả các tập tin nguồn, bao gồm cả student.c
SRCS := main.c $(SRC_DIR)/Menu.c $(SRC_DIR)/student.c

# Tất cả các tập tin đối tượng
OBJS := $(SRCS:%.c=%.o)

# Đối với mỗi tập tin .c, tạo một tập tin đối tượng .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ -I$(INC_DIR)

# Mục tiêu mặc định: tạo chương trình chính
all: $(OBJS)
	$(CC) -o main $(OBJS)

# Loại bỏ tất cả các tập tin đối tượng và chương trình chính
clean:
	rm -rf main $(OBJS)
