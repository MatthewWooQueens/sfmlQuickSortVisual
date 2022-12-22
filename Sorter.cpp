#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System/Clock.hpp>
#include <exception>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <random>


const int width = 1200;
const int height = 400;

void draw(sf::RenderWindow &window,std::vector<int> &block){
    window.clear(sf::Color::Black);
    for(int x = 0;x<block.size();x++){
        sf::RectangleShape bar(sf::Vector2f(10.0f,(float) block[x]*2));
        bar.setOrigin(0,block[x]*2);
        bar.setPosition(x*10,400);
        window.draw(bar);
    }
    //sf::RectangleShape bar(sf::Vector2f(10.0f,50.0f));
    /*bar.setOrigin(5,25);
    bar.setPosition(width/2,height-20);
    window.draw(bar);
    bar.setPosition(width-1,height-1);
    window.draw(bar);
    bar.setPosition(0,0);
    window.draw(bar);*/

    window.display();
}

void delay(sf::RenderWindow &window){
    sf::Clock clock;
    sf::Event event;
    float time = 0.0f;
    float DELAY_TIME = 1.0f;
    clock.restart();
    while(true){
        if(time >= DELAY_TIME){
            time = 0;
            break;
        }
    time += clock.getElapsedTime().asSeconds();
    std::cout << time << " " << DELAY_TIME << std::endl;
    window.pollEvent(event);
    }
}


//LR Quicksort
void quicksort(sf::RenderWindow &window,std::vector<int> &block, int front, int end){
    sf::Clock clock;
    sf::Event event;
    float time = 0.0f;
	//clock.restart();
    float DELAY_TIME = 1.0f;
    int pivot = block[front];
    int low = front, high = end;
    //std::cout << block[0]<<block[1]<<block[2]<<block[3]<<block[4]<<block[5]<<block[6] << std::endl;
    //std::cout << high << low<< std::endl;
    if(low < high){
        while(window.isOpen()){
            //std::cout << "entered" << std::endl;
            while(block[low] <= pivot){
                low++;
            }
            while(block[high] > pivot){
                high--;
            }
            clock.restart();
            while(true){
                if(time >= DELAY_TIME){
                    time = 0;
                    //clock.restart();
                    break;
                }
                time += clock.getElapsedTime().asSeconds();
                std::cout << time << " " << DELAY_TIME << std::endl;
                window.pollEvent(event);
            }
            if(low >= high){
                int temp = pivot;
                block[front] = block[high];
                block[high] = temp;
                draw(window,block);
                break;
            }else{
                int temp = block[low];
                block[low] = block[high];
                block[high] = temp;
                draw(window,block);
            }
        //std::cout << high << low << std::endl;
            window.pollEvent(event);
            /*if(event.type == sf::Event::Closed){
                window.close();
            }*/
        //SOMETHING KEEPS TRIGGERING CLOSE EARLY
        }
        quicksort(window,block,front,high-1);
        quicksort(window,block,high+1,end);
    }
}

int main(){
    sf::RenderWindow window(sf::VideoMode(1200, 400), "SFML window");
    sf::Event event;
    GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;

    std::vector<int> blocks; //= {0,9,6,3,4,2,7,33,21,2,40,13,19,10,11,17,19};
    srand(time(NULL));
    const int max = 200;
    for(int x=0;x<100;x++){
        blocks.push_back(rand()%max);
    }

    bool done = false;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            std::cout<<"poll"<<std::endl;
        }
        window.display();
        if(done == false){
            quicksort(window, blocks, 0, blocks.size()-1);
            done = true;
            std::cout << "The End";
            draw(window,blocks);
        }
        //std::cout << "" << std::endl;

    }


    return 0;
}