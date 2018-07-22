# Redo_UndoOpertaion
Cut copy Operations Performed
The day to day operations we perform like the basic cut , copy and paste operations is one of the major challenge for the engineers
and stacks are used as the datastructure . Small But a useful project.

There are 4 options
1. Insert
2. Delete
3. Redo
4. Undo

There are two stacks, an undo stack and a redo stack. Whenever a user action is performed, a pair of action structures are pushed onto the undo stack - the pair has the action itself and its inverse.

When Undo is invoked, we pop the pair from the undo stack and put it on the redo stack. We invoke the second action (the inverse)

When Redo is invoked, we pop the pair from the redo stack and push it on the undo stack, we invoke the first action in the pair.

Undoability and Redoability are defined by whether either stack is empty.

When the user performs any action, the redo stack is cleared.
