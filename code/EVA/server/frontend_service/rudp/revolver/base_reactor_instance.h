#ifndef __BASE_REACTOR_INSTANCE_H
#define __BASE_REACTOR_INSTANCE_H

#include "base_select_reactor.h"
#include "base_epoll_reactor.h"

#if defined(WIN32) || defined(__APPLE__)
#define REACTOR_CREATE   CRUDPSingleton<CSelectReator>::instance
#define REACTOR_INSTANCE CRUDPSingleton<CSelectReator>::instance
#define REACTOR_DESTROY  CRUDPSingleton<CSelectReator>::destroy
#else
#define REACTOR_CREATE   CRUDPSingleton<CEpollReactor>::instance
#define REACTOR_INSTANCE CRUDPSingleton<CEpollReactor>::instance
#define REACTOR_DESTROY  CRUDPSingleton<CEpollReactor>::destroy
#endif

#endif
