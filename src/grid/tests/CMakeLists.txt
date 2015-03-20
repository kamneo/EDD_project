#Ajoute l'executable pour chaque test
add_executable(test-grid-1 test-grid-1.c)
add_executable(test-grid-2 test-grid-2.c)
add_executable(test-grid-3 test-grid-3.c)
add_executable(test-grid-4 test-grid-4.c)
add_executable(test-grid-5 test-grid-5.c)
add_executable(test-grid-6 test-grid-6.c)
add_executable(test-play test-play.c)

#ajoute les dependances pour chaque test
target_link_libraries(test-grid-1 grid m)
target_link_libraries(test-grid-2 grid m)
target_link_libraries(test-grid-3 grid m)
target_link_libraries(test-grid-4 grid m)
target_link_libraries(test-grid-5 grid m)
target_link_libraries(test-grid-6 grid m)
target_link_libraries(test-play grid m)

#Ajoute les test au make
add_test (test_new_grid test-grid-1)
add_test (test_homogeneite_add_tile test-grid-2)
add_test (test_copy_grid test-grid-3)
add_test (test_can_move test-grid-4)
add_test (test_game_over test-grid-5)
add_test (test_do_move test-grid-6)
add_test (test_basic_strategy test-play)

#Definition des propriétés de succés aux test
set_tests_properties(test_new_grid test_homogeneite_add_tile test_copy_grid test_can_move test_game_over test_do_move test_basic_strategy PROPERTIES TIMEOUT 2)
