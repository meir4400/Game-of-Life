Game of Life - Implementation in C

Game of Life is a game that was invented by John Horton Conway in 1970.
 in this game there is a board with cells.
 each cell could be either live or dead.
 the game is "zero players game" and manages itself since we initialize it.
 in initialize we should insert numbers of rows, columns and max number of live cells.
 when done, the game is initialized and the board is created. 
in each step in game, all board cells
 are checked to update their status, whether live or dead.
the game's rules can be found in wikipedia.


the program structure and progress:

there are only two main files. Controller and Board.
Controller ask for data, initialize the game, makes array of live cells
in random number and invokes the Board file.
Board creats the board as a matrix of "char" s.
then, in each game step:

run in loop on all live cells.
send each one and all its neighbors to set their state.
the state of each cell, either neighbor or cell itself, will be set
according to the number of its live neighbors.

after checking cells all, we update the board, free the previous
live cells array, allocate and create a new one with updated number of live cells.

print the board and go to next step.

repeat it all while there are live cells in game.


improvments:
each checked cell, will be remarked as LIVE / DEAD / SHOULD_LIVE or SHOULD_DEAD.
in this approach we can know what is cell's current state and what is the future
without using help array or running again on all board.
we must distinguish betwwen those states beacause we cannot change cell's state
untill run on all cells.
another improvment is the running in each step only on the live cells and their neighbors.
it could happen due to the fact that other cells are not changing.


attention !!!!!
many times the game will never ends.
it happens for example when there are square of live cells. so each cell has
3 neighbors, so its state does not change.
when this happens, press ctrl + c to terminate the program.


compile: gcc -Wall Board.c Controller.c Main.c -o app
run: .\app.exe



משחק החיים - מימוש בשפת c


אלגוריתם ריצת המשחק:

בלולאה (אחרי אתחול הנתונים והלוח) :
עוברים על מערך התאים החיים
עבור כל תא, שולחים לבדיקה את שמונת שכניו (לא כולל אותו עצמו) 
לכל שכן כזה בודקים את כל שכניו, ובהתאם לתוצאה, מסמנים אותו כחי/ מת/ עומד למות/ לחיות 
אחרי שעברנו על כל השכנים, שולחים לבדיקה את התא עצמו (התא הנוכחי במערך התאים החיים), ובהתאם לתוצאה, מסמנים אותו כנ"ל
ממשיכים לתא הבא במערך התאים החיים.
בסיום המעבר על כל הלוח ועדכונו, בונים מחדש את מערך התאים החיים ומדפיסים את הלוח.
חוזרים לתחילת הלולאה.


נשים לב שלא בודקים כל תא בלוח אלא רק את תאי השכנים של כל תא חי, כך אנו משיגים יעילות גבוהה בריצת המשחק
בנוסף, יש ארבעה מצבים לכל תא- חי, מת, עומד לחיות, עומד למות. 
כך אפשר לבדוק בצעד הנוכחי האם התא חי או מת וגם לתת לו ערך עבור הצעד הבא בלי שנהרוס את ערכו הקיים


קימפול והרצה:
gcc -Wall Board.c Controller.c Main.c -o app
.\app.exe