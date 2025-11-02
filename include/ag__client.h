#ifndef AG__CLIENT_H
#define AG__CLIENT_H

#include "ag__defines.h"

void m_process__create_client__ag(
        Process *p_this_process,
        Game *p_game);

void m_process__deserialize_client__ag(
        Process *p_this_process,
        Game *p_game);

void m_process__serialize_client__ag(
        Process *p_this_process,
        Game *p_game);

#endif
