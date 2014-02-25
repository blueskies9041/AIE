#ifndef _ACCESSORTEMPLATE_H_
#define _ACCESSORTEMPLATE_H_

/* Accessor Template for possible later Use */
enum Accessor_type { rvalue, lvalue };

template< typename T, Accessor_type = rvalue >
class Accessors;

template< typename T >
class Accessors< T, lvalue > {
private:
	T m_t;
public:
	Accessors< T, lvalue >() {}
	explicit Accessors< T, lvalue >( const T &t ) : m_t( t ) {}

	T &operator() () { return m_t; }
	const T &operator() () const { return m_t; }
};

template< typename T >
class Accessors< T, rvalue > {
private:
	T m_t;
public:
	Accessors< T, rvalue >() {}
	explicit Accessors< T, rvalue >( const T &t ) : m_t( t ) {}

	const T &operator() () const { return m_t; }
	void operator() ( const T &t ) { m_t = t; }
};

#endif