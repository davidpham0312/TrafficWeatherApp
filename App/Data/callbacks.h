#ifndef CALLBACKS_H
#define CALLBACKS_H


template<class T>
typedef void (*OnDataReady)(T messages, bool success);
typedef void (*OnMessagesStored)(void);

#endif // CALLBACKS_H
