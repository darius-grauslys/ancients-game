#ifndef ALIAS_TEXTURE_REGISTRAR_H
#define ALIAS_TEXTURE_REGISTRAR_H

#include "defines.h"

extern Texture_Name__c_str name_of__texture__ground;
extern Texture_Name__c_str name_of__texture__cover;
extern Texture_Name__c_str name_of__texture__ui;
extern Texture_Name__c_str name_of__texture__font__large;
extern Texture_Name__c_str name_of__texture__ui_sprites__16x16;

extern Texture_Name__c_str name_of__texture__player;
extern Texture_Name__c_str name_of__texture__skeleton;

void register_aliased_textures(
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Game *p_game);

void register_aliased_textures_for__world(
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Game *p_game);

void register_aliased_textures_for__entities(
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Game *p_game);

#endif
