#include "genres_map.h"

GenresMap::GenresMap()
{    
    FB2Map.insert("sf_history", "Альтернативная история");
    FB2Map.insert("sf_action", "Боевая фантастика");
    FB2Map.insert("sf_epic", "Эпическая фантастика");
    FB2Map.insert("sf_heroic", "Героическая фантастика");
    FB2Map.insert("sf_detective", "Детективная фантастика");
    FB2Map.insert("sf_cyberpunk", "Киберпанк");
    FB2Map.insert("sf_space", "Космическая фантастика");
    FB2Map.insert("sf_social", "Социально-психологическая фантастика");
    FB2Map.insert("sf_horror", "Ужасы и Мистика");
    FB2Map.insert("sf_humor", "Юмористическая фантастика");
    FB2Map.insert("sf_fantasy", "Фэнтези");
    FB2Map.insert("sf", "Научная Фантастика");

    FB2Map.insert("det_classic", "Классический детектив");
    FB2Map.insert("det_police", "Полицейский детектив");
    FB2Map.insert("det_action", "Боевик");
    FB2Map.insert("det_irony", "Иронический детектив");
    FB2Map.insert("det_history", "Исторический детектив");
    FB2Map.insert("det_espionage", "Шпионский детектив");
    FB2Map.insert("det_crime", "Криминальный детектив");
    FB2Map.insert("det_political", "Политический детектив");
    FB2Map.insert("det_maniac", "Маньяки");
    FB2Map.insert("det_hard", "Крутой детектив");
    FB2Map.insert("thriller", "Триллер");
    FB2Map.insert("detective", "Детектив");

    FB2Map.insert("prose_classic", "Классическая проза");
    FB2Map.insert("prose_history", "Историческая проза");
    FB2Map.insert("prose_contemporary", "Современная проза");
    FB2Map.insert("prose_counter", "Контркультура");
    FB2Map.insert("prose_rus_classic", "Русская классическая проза");
    FB2Map.insert("prose_su_classics", "Советская классическая проза");

    FB2Map.insert("love_contemporary", "Современные любовные романы");
    FB2Map.insert("love_history", "Исторические любовные романы");
    FB2Map.insert("love_detective", "Остросюжетные любовные романы");
    FB2Map.insert("love_short", "Короткие любовные романы");
    FB2Map.insert("love_erotica", "Эротика");

    FB2Map.insert("adv_western", "Вестерн");
    FB2Map.insert("adv_history", "Исторические приключения");
    FB2Map.insert("adv_indian", "Приключения про индейцев");
    FB2Map.insert("adv_maritime", "Морские приключения");
    FB2Map.insert("adv_geo", "Путешествия и география");
    FB2Map.insert("adv_animal", "Природа и животные");
    FB2Map.insert("adventure", "Приключения");

    FB2Map.insert("child_tale", "Сказка");
    FB2Map.insert("child_verse", "Детские стихи");
    FB2Map.insert("child_prose", "Детскиая проза");
    FB2Map.insert("child_sf", "Детская фантастика");
    FB2Map.insert("child_det", "Детские остросюжетные");
    FB2Map.insert("child_adv", "Детские приключения");
    FB2Map.insert("child_education", "Детская образовательная литература");
    FB2Map.insert("children", "Детская литература");

    FB2Map.insert("poetry", "Поэзия");
    FB2Map.insert("dramaturgy", "Драматургия");

    FB2Map.insert("antique_ant", "Античная литература");
    FB2Map.insert("antique_european", "Европейская старинная литература");
    FB2Map.insert("antique_russian", "Древнерусская литература");
    FB2Map.insert("antique_east", "Древневосточная литература");
    FB2Map.insert("antique_myths", "Мифы. Легенды. Эпос");
    FB2Map.insert("antique", "Старинная литература");

    FB2Map.insert("sci_history", "История");
    FB2Map.insert("sci_psychology", "Психология");
    FB2Map.insert("sci_culture", "Культурология");
    FB2Map.insert("sci_religion", "Религиоведение");
    FB2Map.insert("sci_philosophy", "Философия");
    FB2Map.insert("sci_politics", "Политика");
    FB2Map.insert("sci_business", "Деловая литература");
    FB2Map.insert("sci_juris", "Юриспруденция");
    FB2Map.insert("sci_linguistic", "Языкознание");
    FB2Map.insert("sci_medicine", "Медицина");
    FB2Map.insert("sci_phys", "Физика");
    FB2Map.insert("sci_math", "Математика");
    FB2Map.insert("sci_chem", "Химия");
    FB2Map.insert("sci_biology", "Биология");
    FB2Map.insert("sci_tech", "Технические науки");
    FB2Map.insert("science", "Научная литература");

    FB2Map.insert("comp_www", "Интернет");
    FB2Map.insert("comp_programming", "Программирование");
    FB2Map.insert("comp_hard", "Компьютерное 'железо'");
    FB2Map.insert("comp_soft", "Программы");
    FB2Map.insert("comp_db", "Базы данных");
    FB2Map.insert("comp_osnet", "ОС и Сети");
    FB2Map.insert("computers", "Околокомпьтерная литература");

    FB2Map.insert("ref_encyc", "Энциклопедии");
    FB2Map.insert("ref_dict", "Словари");
    FB2Map.insert("ref_ref", "Справочники");
    FB2Map.insert("ref_guide", "Руководства");
    FB2Map.insert("reference", "Справочная литература");

    FB2Map.insert("nonf_biography", "Биографии и Мемуары");
    FB2Map.insert("nonf_publicism", "Публицистика");
    FB2Map.insert("nonf_criticism", "Критика");
    FB2Map.insert("design", "Искусство и Дизайн");
    FB2Map.insert("nonfiction", "Документальная литература");

    FB2Map.insert("religion_rel", "Религия");
    FB2Map.insert("religion_esoterics", "Эзотерика");
    FB2Map.insert("religion_self", "Самосовершенствование");
    FB2Map.insert("religion", "Религионая литература");

    FB2Map.insert("humor_anecdote", "Анекдоты");
    FB2Map.insert("humor_prose", "Юмористическая проза");
    FB2Map.insert("humor_verse", "Юмористические стихи");
    FB2Map.insert("humor", "Юмор");

    FB2Map.insert("home_cooking", "Кулинария");
    FB2Map.insert("home_pets", "Домашние животные");
    FB2Map.insert("home_crafts", "Хобби и ремесла");
    FB2Map.insert("home_entertain", "Развлечения");
    FB2Map.insert("home_health", "Здоровье");
    FB2Map.insert("home_garden", "Сад и огород");
    FB2Map.insert("home_diy", "Сделай сам");
    FB2Map.insert("home_sport", "Спорт");
    FB2Map.insert("home_sex", "Эротика, Секс");
    FB2Map.insert("home", "Домоводство");
}


QString GenresMap::getFB2Genre(const QString &key) const
{
    if (FB2Map.contains(key))
        return FB2Map[key];
    return "";
}
