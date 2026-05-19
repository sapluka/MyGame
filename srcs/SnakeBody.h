#include "Snake.h"
#include "SnakeHead.h"
#include "vec2.h"
#include <vector>
class SnakeBody : public Snake
{
    public:
        SnakeBody():Snake()
        {
        }
        ~SnakeBody()=default;        
        void updateBodyPosition();//set position
        const std::vector<vec2>& getLastPositions() const;
        vec2 getPosition() const
        {
            return position;
        }

        // 必须实现基类的纯虚函数，否则它是一个抽象类，无法被实例化
        void move() override {}
        void changeDirection(int dx, int dy) override {}
    private:     

};