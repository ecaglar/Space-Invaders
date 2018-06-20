#ifndef __SINGLETON_HPP_
#define __SINGLETON_HPP_

/*
	Singleton Template
	The class which you want it to be singleton, just extends this class
	and make it friend to your class in order to access invisible ctor/dtor

*/

template <class T>
class Singleton
{
public:
		static T* Instance() {

			if(!m_pInstance) m_pInstance = new T;
			
			return m_pInstance;
		}

protected:

	Singleton(void){};
	~Singleton(void){}
private:
		Singleton(Singleton const&);
		Singleton& operator=(Singleton const&);
		static T* m_pInstance;
};
	
template <class T> T* Singleton<T>::m_pInstance=NULL;

#endif
