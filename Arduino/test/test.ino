#define METAL_PIN 8
#define METAL_THRESHOLD
#define CHECK_MILLIS (int)200

int metal_value = 0;
int counter = 0;
bool check_metal = false;
bool wait_EV3 = false;
bool EV3_count = 0;

void triggerEV3(){

}

void setup(){
  Serial.begin(9600);
}

void loop(){
    metal_value = analogRead(METAL_PIN);
    if(!check_metal && !wait_EV3){
        if(metal_value > METAL_THRESHOLD){
            check_metal = true
        }
    }else if(check_metal){
        if(counter = CHECK_MILLIS/50){
            check_metal = false;
            conter = 0;
            triggerEV3();
        }
        else if(metal_value > METAL_THRESHOLD){
            counter++;
        }
    }
    if(!check_metal){
        sleep(1000);
    }else{
        sleep(50);
    }

}
