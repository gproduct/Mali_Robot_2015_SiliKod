#define TACTIC_ONE_POSITION_COUNT	2

typedef enum
{
	TACTIC_ONE = 1,
	TACTIC_TWO,
	COLLISION
}robotStates;

typedef struct
{
	int distance;
	unsigned char speed;
	char (*detectionCallback)(unsigned long);
}moveOnDirectionFields;

void yellowSide(void);
void greenSide(void);
