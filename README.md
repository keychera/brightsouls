# ![alt tag](https://cloud.githubusercontent.com/assets/23205405/20060403/97729e1a-a52d-11e6-922b-a879f2b7212a.jpg)
##**FOR BRIGHTER (TUBES) FUTURE**

* **Instructions**
  * Map navigation
  * Skill navigation
  * Battle system

* **Commit Changelog Details:**
 * "Added cheat and reworked status" <HEAD>
     - Input "99" in main menu to use cheat
     - Reworked player & enemy status
 * "Fix game balance" <cc1bbd3>
     - Fix battle issue (not a good solution though, just a workaround), detailed issue pm me
     - Added more enemy
     - Player Max HP decreased from 25 to 23
     - Player STR decreased from 8 to 6
     - Player DEF decreased from 7 to 5

 * "COMBINED SKILL + MAP + BATTLE! the gameplay is visible now + cleanup" + "Fixing skill issue" <f908f46> <2901768>
     - SKILL , MAP, BATTLE
     - add -lm on compiling command for math.h
     - no issue so far
     - **NOTICE** ON INCOMPLETE FEATURE BELOW
     - enemy id passing to battle module is not handled
     - player stat is not handled
     - battle_outcome and its effect on map and skill is not handled
     - probably unsync feature on level up handled by battle module and skillpoint increase by skill module
     - spawnenemy,mainmenu,and other thing I probably miss is not combined

 * " fixing issue #4, changes on stacklist and battle_enemyLoad " + "Queue rep for player actions and stacklist not using list_str anymore" <70a821e> <6cb80da>
     - issue caused by pointer inconsistency in stacklist is solved
     - battle_enemyLoad and battle_displayAction work properly now
     - Queue is back
     - Stacklist and list_str is combined(again, I should've known that it's a bad idea!)
     
 * "Manual merging Skill and Battle feature and reorganize txt file " <a42e502>
     - manually merging Skill feature by kevjo and this Battle feature to test compatibility
     
  * "Merge deletestringh and master" + "further little fix" <f908f46> <2901768>
     - string.h is replaced by mystring.h
     - queuelist is temporarily removed
     - resolved merge conflict
     - resolved issue on getting external string that ends with '\r'
     - clearscreen with "clear()" command, defined in brightsoul.h
     
  * "Added enemy conclude" <78ce3c4>
     - Battle_outcome has return value now
     - Added player status calculation
     - Edited enemy exp calculation
     - Reworked player and enemy base status

  * "Fully working monster database" <0ceaffa>
     - Enemy Load is working now
     - Added monsterLVL as argument in battle_initiate and battle_playerLoad
     - Added new adt
     - Changed currentAct variable type in battle_engage from infotype to array of char
     - Edited (infotype* X) argument in Pop procedure to (infotype X) to avoid double pointer error 

* **Using MakeFile:**
	 - run command "make" on main_dir
     - run "./brightsouls"
 
* **Compiling Command:**
```bash
	gcc battle.c brightsoul.c lilfx.c mesinkar.c mesinkata.c stacklist.c queue.c reader.c narrate.c monsterdb.c mystring.c tree.c skill.c listskill.c map.c mypoint.c matriks.c spawnenemy.c -o atest -lm
```
