# ![alt tag](https://cloud.githubusercontent.com/assets/23205405/20060403/97729e1a-a52d-11e6-922b-a879f2b7212a.jpg)
##**FOR BRIGHTER (TUBES) FUTURE**

* **Known Issues**
  * Enemy action display problem after round 1

* **Commit Changelog Details:**
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
 
* **Compiling Command:**
```bash
	gcc battle.c brightsoul.c lilfx.c mesinkar.c mesinkata.c stacklist.c queue.c reader.c narrate.c monsterdb.c mystring.c tree.c skill.c listskill.c map.c point.c matriks.c -o atest -lm
```
