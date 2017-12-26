int buzzer = 11;
void setup()
{
	pinMode(buzzer,OUTPUT);
}

void loop()
{
	unsigned char i,j;
	while(1)
	{
		for(i=0;i<80;i++)
		{
			digitalWrite(buzzer,HIGH);
			delay(1);//wait for 1ms
			digitalWrite(buzzer,LOW);
			delay(1);//wait for 1ms
		}
		for(i=0;i<100;i++)
		{
			digitalWrite(buzzer,HIGH);
			delay(2);//wait for 2ms
			digitalWrite(buzzer,LOW);
			delay(2);//wait for 2ms
		}
	}
}
