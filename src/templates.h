#ifndef TEMPLATES_H
#define TEMPLATES_H
#define CAT(X,Y) X##_##Y
#define TEMPLATE(X,Y) CAT(X,Y)
#define node(T) struct TEMPLATE(node, T)
#define deque(T) struct TEMPLATE(deque, T)
#define map(T) struct TEMPLATE(map, T)
#endif
