#pragma once
#include <QWidget>
#include <memory>

/*utils contains static utilities . Convenient to have during the course of development*/
namespace Ps
{
    class Utils
    {
    public:

        static void DestructorMsg(const QString& value);
        static void DestructorMsg(const QObject * const object);
        //tell when and what object has been deleted

        template<typename T, typename... Args>
        static std::unique_ptr<T> make_unique(Args&&... args)
        {
            return std::unique_ptr<T> (new T(std::forward<Args>(args)...));
        }
        //this template makes a unique pointer

    private:
        explicit Utils(const Utils& rhs) = delete;
        Utils& operator= (const Utils& rhs) = delete;
    };
}


