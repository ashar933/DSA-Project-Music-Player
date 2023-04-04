# DSA-Project-Music-Player
A music player for queueing and playing songs using data structures (queue and doubly linked list) written in C.


Sample Input 1:
```
24
create_playlist
create_music_queue
add_song 1 -1
add_song 2 -1
add_song 3 -1
add_song 4 -1
display_playlist
delete_song 2
display_playlist
play_next
display_playlist
search_and_play 3
play_previous
play_previous
play_previous
play_next
play_next
insert_to_queue 1
display_playlist
shuffle 1
display_playlist
debug 5 3
delete_playlist
clear_music_queue
```
Sample Output 1:
```
4 3 2 1 
4 3 1 
Playing: 4
4 3 1 
Playing: 3
Playing: 4
Playing: 1
Playing: 3
Playing: 1
Playing: 4
4 3 1 
4 1 3 
Found cycle at: 3
```
Sample Input 2:
```
31
create_playlist
create_music_queue
add_song 1 -1
add_song 2 -1
add_song 3 -1
add_song 4 -1
add_song 5 4
add_song 6 -2
display_playlist
delete_song 2
display_playlist
delete_song 4
play_next
display_playlist
search_and_play 2
play_previous
insert_to_queue 1
insert_to_queue 2
search_and_play 3
display_playlist
shuffle 2
display_playlist
debug 5 6
debug 5 3
add_song 10 6
add_song 11 3
display_playlist
shuffle 3
display_playlist
delete_playlist
clear_music_queue
```
Sample Output 2:
```
4 5 3 2 1 6 
4 5 3 1 6 
Playing: 5
5 3 1 6 
Playing: 6
Playing: 3
5 3 1 6 
3 5 6 1 
No loop!
Found cycle at: 3
3 11 5 6 10 1 
5 11 3 1 10 6
```
