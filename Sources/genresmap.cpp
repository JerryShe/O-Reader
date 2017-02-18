#include "genresmap.h"

GenresMap::GenresMap()
{    
    FB2GMap.insert("sf_history","Альтернативная история");
    FB2GMap.insert("sf_action","Боевая фантастика");
    FB2GMap.insert("sf_epic","Эпическая фантастика");
    FB2GMap.insert("sf_heroic","Героическая фантастика");
    FB2GMap.insert("sf_detective","Детективная фантастика");
    FB2GMap.insert("sf_cyberpunk","Киберпанк");
    FB2GMap.insert("sf_space","Космическая фантастика");
    FB2GMap.insert("sf_social","Социально-психологическая фантастика");
    FB2GMap.insert("sf_horror","Ужасы и Мистика");
    FB2GMap.insert("sf_humor","Юмористическая фантастика");
    FB2GMap.insert("sf_fantasy","Фэнтези");
    FB2GMap.insert("sf","Научная Фантастика");

    FB2GMap.insert("det_classic","Классический детектив");
    FB2GMap.insert("det_police","Полицейский детектив");
    FB2GMap.insert("det_action","Боевик");
    FB2GMap.insert("det_irony","Иронический детектив");
    FB2GMap.insert("det_history","Исторический детектив");
    FB2GMap.insert("det_espionage","Шпионский детектив");
    FB2GMap.insert("det_crime","Криминальный детектив");
    FB2GMap.insert("det_political","Политический детектив");
    FB2GMap.insert("det_maniac","Маньяки");
    FB2GMap.insert("det_hard","Крутой детектив");
    FB2GMap.insert("thriller","Триллер");
    FB2GMap.insert("detective","Детектив");

    FB2GMap.insert("prose_classic","Классическая проза");
    FB2GMap.insert("prose_history","Историческая проза");
    FB2GMap.insert("prose_contemporary","Современная проза");
    FB2GMap.insert("prose_counter","Контркультура");
    FB2GMap.insert("prose_rus_classic","Русская классическая проза");
    FB2GMap.insert("prose_su_classics","Советская классическая проза");

    FB2GMap.insert("love_contemporary","Современные любовные романы");
    FB2GMap.insert("love_history","Исторические любовные романы");
    FB2GMap.insert("love_detective","Остросюжетные любовные романы");
    FB2GMap.insert("love_short","Короткие любовные романы");
    FB2GMap.insert("love_erotica","Эротика");

    FB2GMap.insert("adv_western","Вестерн");
    FB2GMap.insert("adv_history","Исторические приключения");
    FB2GMap.insert("adv_indian","Приключения про индейцев");
    FB2GMap.insert("adv_maritime","Морские приключения");
    FB2GMap.insert("adv_geo","Путешествия и география");
    FB2GMap.insert("adv_animal","Природа и животные");
    FB2GMap.insert("adventure","Приключения");

    FB2GMap.insert("child_tale","Сказка");
    FB2GMap.insert("child_verse","Детские стихи");
    FB2GMap.insert("child_prose","Детскиая проза");
    FB2GMap.insert("child_sf","Детская фантастика");
    FB2GMap.insert("child_det","Детские остросюжетные");
    FB2GMap.insert("child_adv","Детские приключения");
    FB2GMap.insert("child_education","Детская образовательная литература");
    FB2GMap.insert("children","Детская литература");

    FB2GMap.insert("poetry","Поэзия");
    FB2GMap.insert("dramaturgy","Драматургия");

    FB2GMap.insert("antique_ant","Античная литература");
    FB2GMap.insert("antique_european","Европейская старинная литература");
    FB2GMap.insert("antique_russian","Древнерусская литература");
    FB2GMap.insert("antique_east","Древневосточная литература");
    FB2GMap.insert("antique_myths","Мифы. Легенды. Эпос");
    FB2GMap.insert("antique","Старинная литература");

    FB2GMap.insert("sci_history","История");
    FB2GMap.insert("sci_psychology","Психология");
    FB2GMap.insert("sci_culture","Культурология");
    FB2GMap.insert("sci_religion","Религиоведение");
    FB2GMap.insert("sci_philosophy","Философия");
    FB2GMap.insert("sci_politics","Политика");
    FB2GMap.insert("sci_business","Деловая литература");
    FB2GMap.insert("sci_juris","Юриспруденция");
    FB2GMap.insert("sci_linguistic","Языкознание");
    FB2GMap.insert("sci_medicine","Медицина");
    FB2GMap.insert("sci_phys","Физика");
    FB2GMap.insert("sci_math","Математика");
    FB2GMap.insert("sci_chem","Химия");
    FB2GMap.insert("sci_biology","Биология");
    FB2GMap.insert("sci_tech","Технические науки");
    FB2GMap.insert("science","Научная литература");

    FB2GMap.insert("comp_www","Интернет");
    FB2GMap.insert("comp_programming","Программирование");
    FB2GMap.insert("comp_hard","Компьютерное 'железо'");
    FB2GMap.insert("comp_soft","Программы");
    FB2GMap.insert("comp_db","Базы данных");
    FB2GMap.insert("comp_osnet","ОС и Сети");
    FB2GMap.insert("computers","Околокомпьтерная литература");

    FB2GMap.insert("ref_encyc","Энциклопедии");
    FB2GMap.insert("ref_dict","Словари");
    FB2GMap.insert("ref_ref","Справочники");
    FB2GMap.insert("ref_guide","Руководства");
    FB2GMap.insert("reference","Справочная литература");

    FB2GMap.insert("nonf_biography","Биографии и Мемуары");
    FB2GMap.insert("nonf_publicism","Публицистика");
    FB2GMap.insert("nonf_criticism","Критика");
    FB2GMap.insert("design","Искусство и Дизайн");
    FB2GMap.insert("nonfiction","Документальная литература");

    FB2GMap.insert("religion_rel","Религия");
    FB2GMap.insert("religion_esoterics","Эзотерика");
    FB2GMap.insert("religion_self","Самосовершенствование");
    FB2GMap.insert("religion","Религионая литература");

    FB2GMap.insert("humor_anecdote","Анекдоты");
    FB2GMap.insert("humor_prose","Юмористическая проза");
    FB2GMap.insert("humor_verse","Юмористические стихи");
    FB2GMap.insert("humor","Юмор");

    FB2GMap.insert("home_cooking","Кулинария");
    FB2GMap.insert("home_pets","Домашние животные");
    FB2GMap.insert("home_crafts","Хобби и ремесла");
    FB2GMap.insert("home_entertain","Развлечения");
    FB2GMap.insert("home_health","Здоровье");
    FB2GMap.insert("home_garden","Сад и огород");
    FB2GMap.insert("home_diy","Сделай сам");
    FB2GMap.insert("home_sport","Спорт");
    FB2GMap.insert("home_sex","Эротика, Секс");
    FB2GMap.insert("home","Домоводство");
}


QString GenresMap::getGenreFromMap(const QString &key)
{
    return FB2GMap[key];
}
