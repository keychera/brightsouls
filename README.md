# ![alt tag](https://cloud.githubusercontent.com/assets/23205405/20060403/97729e1a-a52d-11e6-922b-a879f2b7212a.jpg)
##**FOR BRIGHTER (TUBES) FUTURE**

* **Known Issues**
  * Enemy action display problem after round 1

* **Commit Changelog Details:**
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
	gcc battle.c brightsoul.c lilfx.c list_str.c mesinkar.c mesinkata.c queuelist.c stacklist.c reader.c narrate.c monsterdb.c -o atest
```
