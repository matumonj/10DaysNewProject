#pragma once
#include<memory>
template <class T>
inline void Destroy(T*& p) {
	delete p;
	p = nullptr;
}

template <class T>
inline void Destroy_unique(std::unique_ptr<T>& p) {
	p.release();
	//p.reset();
}