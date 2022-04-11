#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_TEST_COUNT 100

/* Get a number from stdin. */
static int get_num() {
	int ret;
	scanf("%d", &ret);
	return ret;
}

/* Setup random seed. */
static void setup_rand() {
	srand(time(NULL));
}

/* Get a random value from 0 to x-1. */
static int get_rand(int x) {
	int partition = RAND_MAX / x;
	int res;

	do res = rand() / partition;
	while (res < 0 || res >= x);
	/* printf("x = %d\n", res); */

	return res;
}

/* Explain the game. */
static void explain() {
	fputs("This is a probability name for algebra mid-term assessment.\n"
	      "\n"
	      "At first, there will a random coin picked from 4 irregular "
	      "coins, with the possibility of getting a head being 0/3, 1/3, "
	      "2/3, 3/3, respectively. The possibilities of getting each of "
	      "the 4 coins are the same.\n"
	      "\n"
	      "Then, you will be presented with three flipping from the picked "
	      "coin. You will have to guess which coin it is from the result.\n",
	      stderr
	);
}

static int get_coin() {
	return get_rand(4);
}

/* Get a flipping result from a coin. true means head and false means tail. */
static bool get_result(int coin) {
	int res = get_rand(3);
	if (res < coin)
		return true;
	else
		return false;
}

/* Play the game for one round. */
static void play() {
	/* 0 means 0/3, etc. */
	int coin = get_coin();

	fputs("The results:\n", stderr);
	for (int i = 0; i < 3; i++) {
		if (get_result(coin))
			puts("H");
		else
			puts("T");
	}

	fputs("Your guess (0 for 0/3, 1 for 1/3, and so on): ", stderr);
	int guess = get_num();

	if (guess == coin)
		fputs("You win!\n", stderr);
	else
		fprintf(stderr, "You lose. It's actually %d/3.\n", coin);
	system("pause");
}

static void test(int test_count) {
	int correct_count = 0;

	/* Do the tests. */
	for (int i = 0; i < test_count; i++) {
		int coin = get_coin();

		int guess = 0;
		for (int i = 0; i < 3; i++)
			if (get_result(coin))
				guess += 1;
		if (guess == coin)
			correct_count += 1;
	}

	/* Print the test result. */
	fprintf(stderr,
		"The optimal strategy got %d out of %d wins, which is "
		"approximately %f.\n",
		correct_count, test_count, (float) correct_count / test_count);
}

int main(int argc, char **argv) {
	int argi;
	
	for (argi = 0; argi < argc; argi++) {
		if (!strcmp(argv[argi], "-t"))
			goto test;
		if (!strcmp(argv[argi], "-h") || !strcmp(argv[argi], "--help")) {
			explain();
			exit(EXIT_SUCCESS);
		}
	}

	explain();
	system("pause");
	setup_rand();
	while (true)
		play();

test:
	test((argi + 1 >= argc) ? 100000 : strtol(argv[argi+1], NULL, 10));
	exit(EXIT_SUCCESS);
}
