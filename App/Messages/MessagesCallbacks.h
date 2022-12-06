#ifndef MESSAGESCALLBACKS_H
#define MESSAGESCALLBACKS_H
#include "message.h"
#include <QList>
using namespace std::placeholders;

#define member_func_to_ptr(ref_to_function, ptr_instance) std::bind(ref_to_function, ptr_instance, _1, _2)
//typedef void (*OnMessagesReady)(QList<Message> messages, bool success);
typedef std::function<void(QList<Message> messages, bool success)>  OnMessagesReady;
typedef void (*OnMessagesStored)(void);
//typedef std::function<void(void)> OnMessagesStored;

#endif // MESSAGESCALLBACKS_H
