#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT 1
#define PRINT 2
#define WRITE 3
#define READ 4
#define EXIT 5

void input_array(int *p_arr, int size);
void print_array(int *p_arr, int size);

unsigned int writeb_arr(const char *filename, void *ptr, size_t size, size_t count);
unsigned int readb_arr(const char *filename, void *ptr, size_t size, size_t count_max);

void get_string(char *str, int num);

int main(int argc, char const *argv[])
{
	char filename[] = "dat";
	int len_max, len = 0;
	printf("nhap chieu dai toi da mang: ");
	scanf("%d", &len_max);
	int a[len_max];

	while (1) {
		/* menu */
		int opts;
		int is_opts_valid;
		do {
			printf("chon 1 trong cac lua chon sau:\n");
			printf("%d. nhap du lieu cho mang\n", INPUT);
			printf("%d. in ra du lieu trong mang\n", PRINT);
			printf("%d. xuat du lieu ra file\n", WRITE);
			printf("%d. nhap du lieu tu file\n", READ);
			printf("%d. thoat\n", EXIT);
			printf("lua chon cua ban la: ");
			scanf("%d", &opts);
			fflush(stdin);
			is_opts_valid = opts >= INPUT && opts <= EXIT;
			if (!is_opts_valid) {
				printf("lua chon cua ban (%d) khong hop le!\n", opts);
			}
		} while (!is_opts_valid);

		switch (opts) {
		case INPUT:
			break;
		case PRINT:
			break;
		case WRITE: {
			int write = writeb_arr(filename, a, sizeof(int), len);
			printf("xuat %d phan tu ra file %s\n", write, filename);
			break;
		}
		case READ: {
			int read = readb_arr(filename, a, sizeof(int), len_max);
			if (read <= len_max) {
				len = read;
				printf("doc %d phan tu tu file %s\n", len, filename);
			} else {
				printf("vuot qua gioi han luu tru cua mang (%d/%d)\n", read, len_max);
			}
			break;
		}
		case EXIT:
			exit(0);
		default:
			printf("-> chuong chinh co loi, xin thu lai\n");
		}
		printf("\n");
	}
	return 0;
}

void input_array(int *p_arr, int size)
{
	int i;
	for (i = 0; i < size; ++i) {
		printf("nhap phan tu thu %d/%d: ", i + 1, size);
		scanf("%d", (p_arr + i));
	}
	printf("\n");
}

void print_array(int *p_arr, int size)
{
	int i;
	for (i = 0; i < size; ++i) {
		printf("%d ", *(p_arr + i));
	}
	printf("\n");
}

unsigned int writeb_arr(const char *filename, void *p_arr, size_t size, size_t count)
{
	unsigned int result;
	FILE *fp = fopen(filename, "wb");
	fwrite(&count, sizeof(size_t), 1, fp);
	result = fwrite(p_arr, size, count, fp);
	fflush(fp);
	fclose(fp);
	return result;
}

unsigned int readb_arr(const char *filename, void *p_arr, size_t size, size_t count_max)
{
	size_t count;
	unsigned int result;
	FILE *fp = fopen(filename, "rb");
	fread(&count, sizeof(size_t), 1, fp);
	/*
	* if count is larger than max,
	* return the count and not read
	* anything to avoid buffer overrun
	*/
	if (count <= count_max) {
		result = fread(p_arr, size, count, fp);
	} else {
		result = count;
	}
	fclose(fp);
	return result;
}

void get_string(char *str, int num)
{
	char *pos;
	fgets(str, num, stdin);
	/* remove newline at the end */
	pos = strchr(str, '\n');
	if (pos != NULL) {
		*pos = '\0';
	}
}
