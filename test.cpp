#include "ev3dev.h"
#include "h_crane.h"


class Crain : public CraneCrane
{
private:
    //ev3dev::color_sensor color_q;               //  black 감지할 때 물건 감지
    ev3dev::infrared_sensor ultrasonic_q;             //  거리가 달라졌을 때 물건 감지
    //ev3dev::sound_sensor sound_q;               //  소리 재생 sound-test.cpp 참고
    ev3dev::motor a;
    ev3dev::motor b; 
    ev3dev::dc_motor c;
    
public:
    // Hardware Configuration
    Crain():m_speed(0), ultrasonic_q(ev3dev::INPUT_2),a(ev3dev::OUTPUT_B), b(ev3dev::OUTPUT_C), c(ev3dev::OUTPUT_A)
    {
        
    }
    
    int m_speed;
    
    bool get_touch_pressed()
    {
        return touch_q.is_pressed();
    }
    
    virtual bool get_down()
    {
        return m_down;
    }

    virtual bool get_up()
    {
        return m_up;
    }

    virtual bool get_right()
    {
        return m_right;
    }

    virtual bool get_left()
    {
        return m_left;
    }

    virtual bool get_enter()
    {
        return m_enter;
    }

    virtual bool get_escape()
    {
        return m_escape;
    }

    virtual int  get_speed()
    {
        return 100;
    }

    virtual void set_down(bool val)
    {
        m_down = val;
    }
    
    virtual void set_up(bool val)
    {
        m_up = val;    
    }
    
    virtual void set_right(bool val)
    {
        m_right = val;   
    }
    virtual void set_left(bool val)
    {
        m_left = val; 
    } 
    
    virtual void set_enter(bool val)
    {
        m_enter = val;    
    }
    
    virtual void set_escape(bool val)
    {
        m_escape = val;    
    }
    
    virtual void set_speed(int val)
    {
        m_speed = val;    
    }
public:
    void example_code();
    void test_code();
};


void Crain::example_code()
{ //This function is for example, you should develop your own logics
    while(get_escape() == false)
    {
        set_down(ev3dev::button::down.pressed());
        set_up(ev3dev::button::up.pressed());
        set_right(ev3dev::button::right.pressed());
        set_left(ev3dev::button::left.pressed());
        set_escape(ev3dev::button::back.pressed());
        set_enter(ev3dev::button::enter.pressed());
        
        if(get_up())
        {   
                a.set_speed_sp(-1*get_speed());
                a.run_forever();
        }   
        if(get_down())
        {
                a.set_speed_sp(get_speed());
                a.run_forever();
        }
        if(get_left())
        {
               b.set_speed_sp(get_speed());
               b.run_forever();
        }
        if(get_right())
        {
               b.set_speed_sp(-1* get_speed());
               b.run_forever();
        }
       
       
        if(!(get_up() | get_down() | get_right() | get_left() | get_enter()))
        {
            a.set_speed_sp(0);
            a.run_forever();
            b.set_speed_sp(0);
            b.run_forever();
        }
    }

    a.stop();
    b.stop();
}



void Crain::test_code()
{
        // int v = 100;
        // set_speed_i (int v); 
        float dis =  ultrasonic_q.distance_centimeters();
        float n;
        int v[3];
        int neck_pos = a.position_sp();
        std::string hold = "hold";
        
        // scan
        while(1)
        {
            b.set_right(true);
            b.set_speed_sp(-1* get_speed());
            b.run_forever();
            
            n = ultrasonic_q.distance_centimeters();      
                
            if(n < dis){                            // if 물체를 감지하면
                v[i] = b.position_sp();
                i++;
            }
                
            if(b.position_sp() == 660){             // End 위치까지 갔을 때
                if(i == 2)
                    break;
                else{   
                    i = 0;
                    b.run_to_abs_pos(0);}          // 시작 위치로
            }  
        }
            
        
        // while문으로(i = 2,1,0)
        for(int i = 2; i >= 0 ; i--)
        {
        // i번째 위치로
            b.set_speed_sp(get_speed());
            b.set_position_sp(v[i]);
        //    b.run_to_abs_pos();
            b.set_stop_action("hold");
        
        // 목내리기
            a.set_down(true);
            a.set_speed_sp(get_speed());
            a.set_position_sp(?);    
            //a.run_to_abs_pos();    //값지정해주기
            a.set_stop_action("hold");
        
        // 집게 벌려서 잡기
        // motor class 
        
        // set_duty_cycle_sp(int v) or set_time_sp(int v)
        // c.set_command("");       //time or duty cycle
        // c.set_polarity("normal or inversed");
        // b.set_stop_action("hold");
        
        // 목 올리기
            a.set_down(true);
            a.set_speed_sp(-1*get_speed());
            a.set_position_sp(neck_pos);
            //a.run_to_abs_pos(neck_pos);  
            a.set_stop_action("hold");
        
        // End  위치로
            b.run_to_abs_pos(660);
            b.set_stop_action("hold");
        
        // 목 내리기
            a.set_down(true);
            a.set_speed_sp(get_speed());
            a.set_position_sp(?);
            a.run_to_abs_pos(?);    //값지정해주기
            a.set_stop_action("hold");
        
        // 집게 벌려서 내려놓기
        
        // 목 올리기
            a.set_down(true);
            a.set_speed_sp(-1*get_speed());
            a.set_position_sp(neck_pos);
            //a.run_to_abs_pos(neck_pos); 
            a.set_stop_action("hold");
        }
    
    
        //Finish
            
        }
    }
}



int main()
{     
    Crain crain;
    
    if(crain.get_touch_pressed()==true)
    {
        
            Crain.test_code();
    
        
    }
    
}
