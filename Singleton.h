#pragma once
class Singleton {
public:
	virtual void init() = 0;
	virtual void release() = 0;
	static Singleton& getInstance();

protected:
	Singleton(const Singleton&) = delete; // Disable copy constructor
	Singleton& operator=(const Singleton&) = delete; // Disable assignment operator

public:
	virtual ~Singleton() {} // virtual destructor for correct object destruction
	Singleton() {} // Protected constructor to prevent instantiation
};
