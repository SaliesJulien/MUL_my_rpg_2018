/*
** EPITECH PROJECT, 2019
** main fonction
** File description:
** my_defender, main function
*/

#include "my.h"
#include "rpg.h"

void create_item2(global_t *global)
{
    global->gameplay->item->axes = sfSprite_create();
    global->gameplay->item->axet = sfTexture_createFromFile(
        "resource/menu/axe.jpg", NULL);
    sfSprite_setTexture(global->gameplay->item->axes,
        global->gameplay->item->axet, sfTrue);
    sfSprite_setPosition(global->gameplay->item->axes, (sfVector2f){477, 912});
    sfSprite_setScale(global->gameplay->item->axes, (sfVector2f){2, 1.7});
    global->gameplay->item->helmets = sfSprite_create();
    global->gameplay->item->helmett = sfTexture_createFromFile(
        "resource/menu/helmet.jpg", NULL);
    sfSprite_setTexture(global->gameplay->item->helmets,
        global->gameplay->item->helmett, sfTrue);
    sfSprite_setPosition(global->gameplay->item->helmets,
        (sfVector2f){607, 912});
    sfSprite_setScale(global->gameplay->item->helmets, (sfVector2f){2, 1.7});
    sfSprite_setTexture(global->gameplay->item->armors,
        global->gameplay->item->armort, sfTrue);
    sfSprite_setPosition(global->gameplay->item->armors,
        (sfVector2f){347, 912});
    sfSprite_setScale(global->gameplay->item->armors, (sfVector2f){2, 1.7});
}

void create_item(global_t *global)
{
    global->gameplay->item->boots = sfSprite_create();
    global->gameplay->item->bootst = sfTexture_createFromFile(
        "resource/menu/boots.png", NULL);
    sfSprite_setTexture(global->gameplay->item->boots,
        global->gameplay->item->bootst, sfTrue);
    sfSprite_setPosition(global->gameplay->item->boots,
        (sfVector2f){217, 280});
    sfSprite_setScale(global->gameplay->item->boots,
        (sfVector2f){3, 2.7});
    global->gameplay->item->orbs = sfSprite_create();
    global->gameplay->item->orbt = sfTexture_createFromFile(
        "resource/menu/orb.jpg", NULL);
    sfSprite_setTexture(global->gameplay->item->orbs, 
        global->gameplay->item->orbt, sfTrue);
    sfSprite_setPosition(global->gameplay->item->orbs, (sfVector2f){217, 912});
    sfSprite_setScale(global->gameplay->item->orbs, (sfVector2f){2, 1.7});
    global->gameplay->item->armors = sfSprite_create();
    global->gameplay->item->armort = sfTexture_createFromFile(
        "resource/menu/armor.jpg", NULL);
    create_item2(global);
}

void draw_item(global_t *global)
{
    sfRenderWindow_drawSprite(global->window,
        global->gameplay->item->boots, NULL);
    sfRenderWindow_drawSprite(global->window, global->gameplay->item->orbs,
        NULL);
    sfRenderWindow_drawSprite(global->window, global->gameplay->item->armors,
        NULL);
    sfRenderWindow_drawSprite(global->window, global->gameplay->item->axes,
        NULL);
    sfRenderWindow_drawSprite(global->window, global->gameplay->item->helmets,
        NULL);
}