

class Door
{
private:
        int doorId;
	int pushButton; // arduino pin for the push button fixed in the door
	int doorState; // state of the door 'open' or 'closed'

public:
	Door(int id, int pb);
	int check_Door();
};

// constructor

Door::Door(int id, int pb) :
doorId(id),pushButton(pb)
{
	pinMode(pushButton, INPUT); // declare pushButton as input
}

//method to check the door state and return the value

int Door::check_Door()
{
	int doorState = digitalRead(pushButton);
	
	return doorState;
	delay(1);
}
