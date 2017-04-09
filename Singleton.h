#pragma once

template <typename T>
class Singleton
{
private:
	static T* instance;

public:
	Singleton() {}
	virtual ~Singleton() {}

	static T* GetInstance()
	{
		if (!instance)
		{
			instance = new T();
		}

		return instance;
	}

	static void Destroy()
	{
		SAFE_DELETE(instance);
	}
};

template <typename T>
T* Singleton<T>::instance = nullptr;