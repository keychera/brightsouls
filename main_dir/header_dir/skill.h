/* File : skill.h */
/* modul program yang mengurus sistem skill */

#ifndef skill_H
#define skill_H

#include "tree.h"

void ImportSkill();
/* Prosedur untuk mengambil data skill dari file eksternal */
void PrintSubTree(addressT P, int n, int a[]);
/* Prosedur rekursi untuk menampilkan tree */
void PrintSkill();
/* Prosedur untuk menampilkan tampilan menu skill */
void LearnSkill();
/* Menu Learn skill */
void UpgradeSkill();
/* Menu Upgade Skill */
void HelpSkill();
/* Menu untuk help */
void SkillMenu();
/* menu yang memproses interface skill */


#endif // skill_H
