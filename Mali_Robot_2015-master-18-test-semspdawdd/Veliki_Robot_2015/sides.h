#define TACTIC_ONE_POSITION_COUNT	2

typedef enum
{
	TACTIC_ONE = 1,
	TACTIC_TWO
}robotStates;

typedef struct
{
	int distance;
	unsigned char speed;
	char (*detectionCallback)(void);
}moveOnDirectionFields;

void yellowSide(void);
void greenSide(void);
