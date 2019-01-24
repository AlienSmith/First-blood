#pragma once
#include <GLFW\glfw3.h>
//use GLFW for non windows application
//This feels like the delta time for the last frame instead of this one
namespace GStar {
	class Time {
	public:
		static Time& Instance() {
			if (!instance) {
				instance = new Time();
			}
			return *instance;
		}
		static void Terminate() {
			if (instance) {
				delete instance;
			}
		}
		Time() :_lasttime(0.0f) {}
		//Call this function after the GLFW window got setup and in every update()
		inline void Tick() {
			_lasttime = _totaltime;
			_totaltime = glfwGetTime();
			_deltatime = _totaltime - _lasttime;
		}
		inline double GetdeltaTime() const{
			return _deltatime;
		}
		inline double GetTotalTime() const {
			return _totaltime;
		}
	private:
		static Time* instance;
		double _deltatime;
		double _lasttime;
		double _totaltime;
	};
}