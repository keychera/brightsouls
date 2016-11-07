# ![alt tag](https://cloud.githubusercontent.com/assets/23205405/20060403/97729e1a-a52d-11e6-922b-a879f2b7212a.jpg)
##**FOR BRIGHTER (TUBES) FUTURE**

* **Commit Changelog Details:**
  * "Fully working monster database" <0ceaffa>
     - Enemy Load is working now
     - Added monsterLVL as argument in battle_initiate and battle_playerLoad
     - Added new adt
     - Changed currentAct variable type in battle_engage from infotype to array of char
     - Edited (infotype* X) argument in Pop procedure to (infotype X) to avoid double pointer error 
 
* **Compiling Command:**
  - gcc battle.c brightsoul.c lilfx.c list_str.c mesinkar.c mesinkata.c queuelist.c stacklist.c reader.c narrate.c monsterdb.c -o atest
