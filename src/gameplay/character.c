/*
** EPITECH PROJECT, 2019
** my_rpg
** File description:
** function to the gameplay
*/

#include "my.h"
#include "rpg.h"

void bottom_left_corner(global_t *global)
{
    sfView_reset(global->gameplay->view, (sfFloatRect){
        global->gameplay->width - 1920, 0, 1920, 1080});
}

void move_vue(global_t *global)
{
    if ((global->gameplay->x > global->gameplay->width - 1920 / 2 - 48) &&
        (global->gameplay->y < 1080 / 2 - 48))
        bottom_left_corner(global);
    else if ((global->gameplay->x < 0 + (1920 / 2) - 48) &&
            (global->gameplay->y < (1080 / 2) - 48))
        sfView_reset(global->gameplay->view, (sfFloatRect){0, 0, 1920, 1080});
    else if ((global->gameplay->x < 0 + 1920 / 2 - 48) &&
            (global->gameplay->y > global->gameplay->lenght - 1080 / 2 - 48))
        top_right_corner(global);
    else if ((global->gameplay->x > global->gameplay->width - 1920 / 2 - 48) &&
            (global->gameplay->y > global->gameplay->lenght - 1080 / 2 - 48))
        bottom_right_corner(global);
    else if (global->gameplay->x > global->gameplay->width - (1920 / 2) - 48 ||
            global->gameplay->x < (1920 / 2) - 48)
        camera_horizontal(global);
    else if (global->gameplay->y > global->gameplay->lenght\
            - (1080 / 2) - 48 || global->gameplay->y < (1080 / 2) - 48)
        vertical_camera(global);
    else
        camera_center(global);
    sfRenderWindow_setView(global->window, global->gameplay->view);
}

void check_other_events(global_t *global)
{
    if (global->gameplay->boss->win_vs_desert_boss == 1) {
        sfSprite_setColor(global->gameplay->boss->sp_desert_boss,
                        sfTransparent);
        global->gameplay->map[32][4] = '0';
    }
    if (global->gameplay->boss->win_vs_hl_boss == 1) {
        sfSprite_setColor(global->gameplay->boss->sp_hl_boss, sfTransparent);
        global->gameplay->map[58][4] = '0';
    }
    if (global->gameplay->boss->quest_fboss == 4 &&
        global->gameplay->boss->s_last_quest == 1)
        global->gameplay->map[9][14] = '0';
    if (global->gameplay->pnj->girl_quest == 0)
        global->gameplay->map[50][50] = '0';
    else
        global->gameplay->map[50][50] = '5';
}

void check_monster_dead(global_t *global)
{
    if (global->scn == 1) {
        if (global->gameplay->boss->win_vs_final_boss == 1) {
            sfSprite_setColor(global->gameplay->boss->sp_final_boss,
                            sfTransparent);
            global->gameplay->map[5][23] = '0';
            global->gameplay->map[5][24] = '0';
        }
        if (global->gameplay->boss->win_vs_winter_boss == 1) {
            sfSprite_setColor(global->gameplay->boss->sp_winter_boss,
                            sfTransparent);
            global->gameplay->map[31][54] = '0';
        }
        check_other_events(global);
    }
    if (global->scn == 13) {
        if (global->gameplay->boss->win_vs_volc_boss == 1)
        sfSprite_setColor(global->gameplay->boss->sp_volc_boss,
                        sfTransparent);
    }
}

int check_events(global_t *global)
{
    while (sfRenderWindow_pollEvent(global->window, &global->event)) {
        check_interaction(global);
        check_interaction_village(global);
        check_interaction_fcp(global);
        check_interaction_castel(global);
        if (global->event.type == sfEvtClosed)
            sfRenderWindow_close(global->window);
        if ((but_is_c(global->event, global->menu->start1) == 1) &&
            (global->scn == 2)) {
            global->scn = 1;
            move_vue(global);
        }
        if ((but_is_c(global->event, global->menu->quit1) == 1) &&
            (global->scn == 2))
            sfRenderWindow_close(global->window);
        if ((but_is_c(global->event, global->pause->inv) == 1) &&
            (global->scn == 2))
            global->scn = 3;
        if ((but_is_c(global->event, global->pause->quest) == 1) &&
            (global->scn == 2))
            global->scn = 4;
        if (global->event.key.code == sfKeyEscape && global->scn != 0)
            global->scn = 2;
        if ((item_is_c(global->event, global->gameplay->item->boots) == 1) &&
            (global->scn == 3)) {
            sfSprite_setPosition(global->gameplay->item->boots,
                (sfVector2f){1045,320});
            sfSprite_setScale(global->gameplay->item->boots,
                (sfVector2f){3.45, 3.45});
        }
        if ((item_is_c(global->event, global->gameplay->item->orbs) == 1) &&
            (global->scn == 3)) {
            sfSprite_setPosition(global->gameplay->item->orbs,
                (sfVector2f){1045, 490});
            sfSprite_setScale(global->gameplay->item->orbs,
                (sfVector2f){2.2, 1.8});
        }
        if ((item_is_c(global->event, global->gameplay->item->armors) == 1) &&
            (global->scn == 3)) {
            sfSprite_setPosition(global->gameplay->item->armors,
                (sfVector2f){1045,320});
            sfSprite_setScale(global->gameplay->item->armors,
                (sfVector2f){1.98, 2.1});
        }
        if ((item_is_c(global->event, global->gameplay->item->axes) == 1) &&
            (global->scn == 3)) {
            sfSprite_setPosition(global->gameplay->item->axes,
                (sfVector2f){1045, 150});
            sfSprite_setScale(global->gameplay->item->axes,
                (sfVector2f){2.15, 2.1});
        }
        if ((item_is_c(global->event, global->gameplay->item->helmets) == 1) &&
            (global->scn == 3)) {
            sfSprite_setPosition(global->gameplay->item->helmets,
                (sfVector2f){1605, 320});
            sfSprite_setScale(global->gameplay->item->helmets,
                (sfVector2f){1.95, 2.0});
        }
        if (global->event.key.code == sfKeyTab && global->scn == -2)
            global->scn = -1;
        if (global->event.key.code == sfKeySpace && (global->scn == -2 ||
            global->scn == -1))
            global->scn = 0;
        move_character(global);
    }
    check_monster_dead(global);
    return (0);
}

void set_position_boss_volc(global_t *global)
{
    sfSprite_setTextureRect(global->gameplay->boss->sp_hl_boss,
    global->gameplay->boss->rect_hl_boss);
    sfSprite_setPosition(global->gameplay->boss->sp_hl_boss,
    (sfVector2f){400, 5700});
    sfSprite_setScale(global->gameplay->boss->sp_hl_boss,
    (sfVector2f){1.5, 1.5});
    sfSprite_setTextureRect(global->gameplay->boss->sp_volc_boss,
    global->gameplay->boss->rect_volc_boss);
    sfSprite_setPosition(global->gameplay->boss->sp_volc_boss,
    (sfVector2f){1200, 1325});
    sfSprite_setScale(global->gameplay->boss->sp_volc_boss,
    (sfVector2f){1.5, 1.5});
}

void set_position_boss(global_t *global)
{
    sfSprite_setTextureRect(global->gameplay->boss->sp_final_boss,
    global->gameplay->boss->rect_final_boss);
    sfSprite_setPosition(global->gameplay->boss->sp_final_boss,
    (sfVector2f){2310, 490});
    sfSprite_setScale(global->gameplay->boss->sp_final_boss,
    (sfVector2f){1.5, 1.5});
    sfSprite_setTextureRect(global->gameplay->boss->sp_winter_boss,
    global->gameplay->boss->rect_winter_boss);
    sfSprite_setPosition(global->gameplay->boss->sp_winter_boss,
    (sfVector2f){5350, 3010});
    sfSprite_setScale(global->gameplay->boss->sp_winter_boss,
    (sfVector2f){1.5, 1.5});
    sfSprite_setTextureRect(global->gameplay->boss->sp_desert_boss,
    global->gameplay->boss->rect_desert_boss);
    sfSprite_setPosition(global->gameplay->boss->sp_desert_boss,
    (sfVector2f){545, 3235});
    sfSprite_setScale(global->gameplay->boss->sp_desert_boss,
    (sfVector2f){1.5, 1.5});
    set_position_boss_volc(global);
}

void set_pnj_position_wm(global_t *global)
{
    sfSprite_setPosition(global->gameplay->pnj->sp_knight_2,
    (sfVector2f){2100, 2700});
    sfSprite_setPosition(global->gameplay->pnj->sp_princess,
    (sfVector2f){2200, 1400});
    sfSprite_setPosition(global->gameplay->pnj->sp_pnj_garden,
    (sfVector2f){2500, 900});
}

void set_pnj_position(global_t *global)
{
    sfSprite_setPosition(global->gameplay->pnj->sprite_pnj_1,
    (sfVector2f){5010, 5000});
    sfSprite_setPosition(global->gameplay->pnj->sprite_pnj_d,
    (sfVector2f){1790, 1900});
    sfSprite_setPosition(global->gameplay->pnj->sprite_pnj_ed,
    (sfVector2f){2790, 2095});
    sfSprite_setPosition(global->gameplay->pnj->sprite_pnj_pech,
    (sfVector2f){3710, 2000});
    sfSprite_setPosition(global->gameplay->pnj->sprite_pnj_bot,
    (sfVector2f){4310, 4600});
    sfSprite_setPosition(global->gameplay->pnj->sp_vil_old,
    (sfVector2f){600, 600});
    sfSprite_setPosition(global->gameplay->pnj->sp_pnj_volc,
    (sfVector2f){1500, 1000});
    sfSprite_setPosition(global->gameplay->pnj->sp_chest_1,
    (sfVector2f){1305, 600});
    sfSprite_setPosition(global->gameplay->pnj->sp_knight_1,
    (sfVector2f){1800, 2700});
    set_pnj_position_wm(global);
}

void set_pnj_scale_castle(global_t *global)
{
    sfSprite_setScale(global->gameplay->pnj->sp_knight_2,
    (sfVector2f){2.08333, 2.08333});
    sfSprite_setScale(global->gameplay->pnj->sp_princess,
    (sfVector2f){2.08333, 2.08333});
    sfSprite_setScale(global->gameplay->pnj->sp_pnj_garden,
    (sfVector2f){2.08333, 2.08333});
}

void set_pnj_scale(global_t *global)
{
    sfSprite_setScale(global->gameplay->pnj->sprite_pnj_d,
    (sfVector2f){2.08333, 2.08333});
    sfSprite_setScale(global->gameplay->pnj->sprite_pnj_1,
    (sfVector2f){2.08333, 2.08333});
    sfSprite_setScale(global->gameplay->pnj->sprite_pnj_ed,
    (sfVector2f){2.08333, 2.08333});
    sfSprite_setScale(global->gameplay->pnj->sprite_pnj_pech,
    (sfVector2f){2.08333, 2.08333});
    sfSprite_setScale(global->gameplay->pnj->sprite_pnj_bot,
    (sfVector2f){2.08333, 2.08333});
    sfSprite_setScale(global->gameplay->pnj->sp_vil_old,
    (sfVector2f){2.08333, 2.08333});
    sfSprite_setScale(global->gameplay->pnj->sp_pnj_volc,
    (sfVector2f){2.08333, 2.08333});
    sfSprite_setScale(global->gameplay->pnj->sp_chest_1,
    (sfVector2f){2.08333, 2.08333});
    sfSprite_setScale(global->gameplay->pnj->sp_knight_1,
    (sfVector2f){2.08333, 2.08333});
    set_pnj_scale_castle(global);
}

void apply_rect_pnj(global_t *global)
{
    sfSprite_setTextureRect(global->gameplay->pnj->sprite_pnj_d,
    global->gameplay->pnj->rect_pnj_d);
    sfSprite_setTextureRect(global->gameplay->pnj->sprite_pnj_1,
    global->gameplay->pnj->rect_pnj_1);
    sfSprite_setTextureRect(global->gameplay->pnj->sprite_pnj_ed,
    global->gameplay->pnj->rect_pnj_ed);
    sfSprite_setTextureRect(global->gameplay->pnj->sprite_pnj_pech,
    global->gameplay->pnj->rect_pnj_pech);
    sfSprite_setTextureRect(global->gameplay->pnj->sprite_pnj_bot,
    global->gameplay->pnj->rect_pnj_bot);
    sfSprite_setTextureRect(global->gameplay->pnj->sp_vil_old,
    global->gameplay->pnj->rect_vil_old);
    sfSprite_setTextureRect(global->gameplay->pnj->sp_pnj_volc,
    global->gameplay->pnj->rect_pnj_volc);
    sfSprite_setTextureRect(global->gameplay->pnj->sp_knight_1,
    global->gameplay->pnj->rect_knight_1);
    sfSprite_setTextureRect(global->gameplay->pnj->sp_knight_2,
    global->gameplay->pnj->rect_knight_2);
    sfSprite_setTextureRect(global->gameplay->pnj->sp_princess,
    global->gameplay->pnj->rect_princess);
}

void set_position(global_t *global)
{
    init_rect_pnj(global);
    apply_rect_pnj(global);
    set_pnj_position(global);
    set_pnj_scale(global);
    sfSprite_setTextureRect(global->gameplay->pnj->sp_pnj_garden,
    global->gameplay->pnj->rect_pnj_garden);
    sfSprite_setPosition(global->gameplay->sprite_man,
    (sfVector2f){global->gameplay->x, global->gameplay->y});
    sfSprite_setScale(global->gameplay->sprite_man,
    (sfVector2f){2.08333, 2.08333});
    set_position_boss(global);
}

void textures(global_t *global)
{
    global->gameplay->boss->volc_boss = sfTexture_createFromFile(
        "resource/fight/Boss.png", NULL);
    global->gameplay->pnj->vil_old = sfTexture_createFromFile(
        "resource/Sprite player/People1.png", NULL);
    global->gameplay->pnj->pnj_volc = sfTexture_createFromFile(
        "resource/Sprite player/People3.png", NULL);
    global->gameplay->pnj->knight_1 = sfTexture_createFromFile(
        "resource/Sprite player/People3.png", NULL);
    global->gameplay->pnj->knight_2 = sfTexture_createFromFile(
        "resource/Sprite player/People3.png", NULL);
    global->gameplay->pnj->princess = sfTexture_createFromFile(
        "resource/Sprite player/People3.png", NULL);
    global->gameplay->pnj->pnj_garden = sfTexture_createFromFile(
        "resource/Sprite player/People1.png", NULL);
    global->gameplay->pnj->chest_1 = sfTexture_createFromFile(
        "resource/Sprite player/Chest.png", NULL);
}

void textures_creation(global_t *global)
{
    global->gameplay->pnj->pnj_d = sfTexture_createFromFile(
        "resource/Sprite player/Actor3.png", NULL);
    global->gameplay->pnj->pnj_1 = sfTexture_createFromFile(
        "resource/Sprite player/player2and3.png", NULL);
    global->gameplay->pnj->pnj_ed = sfTexture_createFromFile(
        "resource/Sprite player/player2and3.png", NULL);
    global->gameplay->pnj->pnj_pech = sfTexture_createFromFile(
        "resource/Sprite player/Actor.png", NULL);
    global->gameplay->pnj->pnj_bot = sfTexture_createFromFile(
        "resource/Sprite player/Actor3.png", NULL);
    global->gameplay->boss->final_boss = sfTexture_createFromFile(
        "resource/fight/bigmonster.png", NULL);
    global->gameplay->boss->winter_boss = sfTexture_createFromFile(
        "resource/fight/bigmonster.png", NULL);
    global->gameplay->boss->desert_boss = sfTexture_createFromFile(
        "resource/fight/bigmonster.png", NULL);
    global->gameplay->boss->hl_boss = sfTexture_createFromFile(
        "resource/fight/bigmonster.png", NULL);
    textures(global);
}

void sprites_creation(global_t *global)
{
    global->gameplay->sprite_backg = sfSprite_create();
    global->gameplay->sprite_man = sfSprite_create();
    global->gameplay->pnj->sprite_pnj_1 = sfSprite_create();
    global->gameplay->pnj->sprite_pnj_d = sfSprite_create();
    global->gameplay->pnj->sprite_pnj_ed = sfSprite_create();
    global->gameplay->pnj->sprite_pnj_pech = sfSprite_create();
    global->gameplay->pnj->sprite_pnj_bot = sfSprite_create();
    global->gameplay->boss->sp_final_boss = sfSprite_create();
    global->gameplay->boss->sp_winter_boss = sfSprite_create();
    global->gameplay->pnj->sp_vil_old = sfSprite_create();
    global->gameplay->pnj->sp_pnj_volc = sfSprite_create();
    global->gameplay->boss->sp_desert_boss = sfSprite_create();
    global->gameplay->boss->sp_hl_boss = sfSprite_create();
    global->gameplay->boss->sp_volc_boss = sfSprite_create();
    global->gameplay->pnj->sp_chest_1 = sfSprite_create();
    global->gameplay->pnj->sp_knight_1 = sfSprite_create();
    global->gameplay->pnj->sp_knight_2 = sfSprite_create();
    global->gameplay->pnj->sp_princess = sfSprite_create();
    global->gameplay->pnj->sp_pnj_garden = sfSprite_create();
}

void create_sprite(global_t *global)
{
    sprites_creation(global);
    textures_creation(global);
    global->gameplay->backg = sfTexture_createFromFile(
        "resource/World Map.jpg", NULL);
    global->gameplay->backg_fcp = sfTexture_createFromFile(
        "resource/Firecamp Plaine.png", NULL);
    global->gameplay->backg_vil = sfTexture_createFromFile(
        "resource/Village de départ.jpg", NULL);
    global->gameplay->backg_cas = sfTexture_createFromFile(
        "resource/Castle.jpg", NULL);
    global->gameplay->backg_vol = sfTexture_createFromFile(
        "resource/Volcano.jpg", NULL);
    create_item(global);
}


void init_gameplay_action(global_t *global)
{
    global->gameplay->pnj->p_text_bot = 0;
    global->gameplay->pnj->p_text_pech = 0;
    global->gameplay->pnj->p_text_ed = 0;
    global->gameplay->pnj->p_text = 0;
    global->gameplay->pnj->girl_quest = 0;
    global->gameplay->pnj->quest_complete = 0;
    global->gameplay->boss->win_vs_final_boss = 0;
    global->gameplay->boss->win_vs_winter_boss = 0;
    global->gameplay->boss->win_vs_desert_boss = 0;
    global->gameplay->pnj->op_chest = 0;
    global->gameplay->boss->s_last_quest2 = 0;
    global->gameplay->pnj->q_volc = 0;
    global->gameplay->boss->win_vs_hl_boss = 0;
    global->gameplay->boss->win_vs_volc_boss = 0;
    global->gameplay->boss->quest_fboss = 0;
    global->gameplay->pnj->vil_papy = 0;
    global->gameplay->pnj->sec_q = \
    "secondary quests: Find the lost girl and bring her back to her mother";
}

void pnj_textures(global_t *global)
{
    sfSprite_setTexture(global->gameplay->pnj->sp_knight_2,
    global->gameplay->pnj->knight_2, sfTrue);
    sfSprite_setTexture(global->gameplay->pnj->sp_princess,
    global->gameplay->pnj->princess, sfTrue);
    sfSprite_setTexture(global->gameplay->pnj->sp_pnj_garden,
    global->gameplay->pnj->pnj_garden, sfTrue);
    sfSprite_setTexture(global->gameplay->boss->sp_final_boss,
    global->gameplay->boss->final_boss, sfTrue);
    sfSprite_setTexture(global->gameplay->boss->sp_volc_boss,
    global->gameplay->boss->volc_boss, sfTrue);
    sfSprite_setTexture(global->gameplay->boss->sp_winter_boss,
    global->gameplay->boss->winter_boss, sfTrue);
    sfSprite_setTexture(global->gameplay->boss->sp_desert_boss,
    global->gameplay->boss->desert_boss, sfTrue);
    sfSprite_setTexture(global->gameplay->boss->sp_hl_boss,
    global->gameplay->boss->hl_boss, sfTrue);
    sfSprite_setTexture(global->gameplay->sprite_backg,
    global->gameplay->backg, sfTrue);
    sfSprite_setTexture(global->gameplay->sprite_man,
    global->gameplay->man, sfTrue);
}

void set_textures(global_t *global)
{
    sfSprite_setTexture(global->gameplay->pnj->sprite_pnj_ed,
    global->gameplay->pnj->pnj_ed, sfTrue);
    sfSprite_setTexture(global->gameplay->pnj->sprite_pnj_d,
    global->gameplay->pnj->pnj_d, sfTrue);
    sfSprite_setTexture(global->gameplay->pnj->sprite_pnj_1,
    global->gameplay->pnj->pnj_1, sfTrue);
    sfSprite_setTexture(global->gameplay->pnj->sprite_pnj_pech,
    global->gameplay->pnj->pnj_pech, sfTrue);
    sfSprite_setTexture(global->gameplay->pnj->sprite_pnj_bot,
    global->gameplay->pnj->pnj_bot, sfTrue);
    sfSprite_setTexture(global->gameplay->pnj->sp_pnj_volc,
    global->gameplay->pnj->pnj_volc, sfTrue);
    sfSprite_setTexture(global->gameplay->pnj->sp_vil_old,
    global->gameplay->pnj->vil_old, sfTrue);
    sfSprite_setTexture(global->gameplay->pnj->sp_chest_1,
    global->gameplay->pnj->chest_1, sfTrue);
    sfSprite_setTexture(global->gameplay->pnj->sp_knight_1,
    global->gameplay->pnj->knight_1, sfTrue);
    pnj_textures(global);
}

void init_texture(global_t *global)
{
    init_gameplay_action(global);
    create_sprite(global);
    if (global->gameplay->player_nb == 1) {
        global->gameplay->man = sfTexture_createFromFile(
                                "resource/Sprite player/Actor.png", NULL);
        set_my_rect_p1(global);
    }
    if (global->gameplay->player_nb == 2) {
        global->gameplay->man = sfTexture_createFromFile(
                            "resource/Sprite player/player2and3.png", NULL);
        set_my_rect_p2(global);
    }
    if (global->gameplay->player_nb == 3) {
        global->gameplay->man = sfTexture_createFromFile(
                               "resource/Sprite player/player2and3.png", NULL);
        set_my_rect_p3(global);
    }
    if (global->gameplay->player_nb == 4) {
        global->gameplay->man = sfTexture_createFromFile(
                                "resource/Sprite player/Actor.png", NULL);
        set_my_rect_p4(global);
    }
    set_textures(global);
    set_position(global);
}

void draw_sprites_scn_1(global_t *global)
{
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->pnj->sprite_pnj_d, NULL);
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->pnj->sprite_pnj_ed, NULL);
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->pnj->sprite_pnj_pech, NULL);
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->pnj->sprite_pnj_bot, NULL);
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->pnj->sp_pnj_volc, NULL);
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->boss->sp_final_boss, NULL);
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->boss->sp_winter_boss, NULL);
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->boss->sp_desert_boss, NULL);
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->boss->sp_hl_boss, NULL);
}

void scn_1(global_t *global)
{
    if (global->gameplay->pnj->girl_quest == 1)
        sfRenderWindow_drawSprite(global->window,
        global->gameplay->pnj->sprite_pnj_1, NULL);
    draw_sprites_scn_1(global);
    switch_in_fight(global);
    display_text(global);
}

void scn_10(global_t *global)
{
    sfSprite_setTextureRect(global->gameplay->pnj->sp_chest_1,
    global->gameplay->pnj->rect_chest_1);
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->pnj->sp_chest_1, NULL);
    display_text_fcp(global);

}

void scn_11(global_t *global)
{
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->pnj->sp_vil_old, NULL);
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->pnj->sp_pnj_garden, NULL);
    display_text_vill(global);
}

void scn_12(global_t *global)
{
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->pnj->sp_knight_1, NULL);
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->pnj->sp_knight_2, NULL);
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->pnj->sp_princess, NULL);
    display_text_castel(global);
}

void scn_13(global_t *global)
{
    fight_in_volc(global);
    sfRenderWindow_drawSprite(global->window,
    global->gameplay->boss->sp_volc_boss, NULL);
}

void set_cursor(global_t *global)
{
    if (global->scn == 2 || global->scn == 3 || global->scn == 4 ||
        global->scn == 5)
        sfRenderWindow_setMouseCursorVisible(global->window, sfTrue);
    else
        sfRenderWindow_setMouseCursorVisible(global->window, sfFalse);
}

void which_scn(global_t *global)
{
    if (global->scn == 1)
        scn_1(global);
    if (global->scn == 11)
        scn_11(global);
    if (global->scn == 10)
        scn_10(global);
    if (global->scn == 12)
        scn_12(global);
    if (global->scn == 13)
        scn_13(global);
}

void draw_sprites(global_t *global)
{
    set_cursor(global);
    global->scn = check_map_change(global, global->scn);
    if (global->scn == 1 || global->scn == 10 || global->scn == 11 ||
        global->scn == 12 || global->scn == 13) {
        sfSprite_setPosition(global->gameplay->sprite_man,
        (sfVector2f){global->gameplay->x, global->gameplay->y});
        sfSprite_setTextureRect(global->gameplay->sprite_man,
        global->gameplay->rect_man);
        sfRenderWindow_drawSprite(global->window,
        global->gameplay->sprite_backg, NULL);
        sfRenderWindow_drawSprite(global->window,
        global->gameplay->sprite_man, NULL);
        which_scn(global);
        sfRenderWindow_display(global->window);
    }
    if (global->scn == 5) {
        sfRenderWindow_setMouseCursorVisible(global->window, sfTrue);
        fight(global);
    }
    display_pause(global);
}