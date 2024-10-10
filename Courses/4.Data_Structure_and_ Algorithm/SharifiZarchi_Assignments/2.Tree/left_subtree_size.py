def change_order(preorder_list, inorder_list):
    if not preorder_list or not inorder_list:
        return []
    head = preorder_list[0]
    ind_of_head_in_inorder = inorder_list.index(head)

    left_inorder = inorder_list[:ind_of_head_in_inorder]
    right_inorder = inorder_list[ind_of_head_in_inorder+1 :]

    left_preorder = preorder_list[1:len(left_inorder)]
    right_preorder = preorder_list[len(left_inorder)+1:]

    left_postorder = change_order(left_preorder, left_inorder)
    right_postorder = change_order(right_preorder, right_inorder)

    return left_postorder + right_postorder + [head]


tester("change_order", change_order)
#example:
#function_call: left_subtree_size([3, 9, 2, 8, 1, 4, 10, 6, 7, 5], [1, 8, 2, 9, 3, 10, 4, 7, 6, 5], 2)
#return value: [1, 8, 2, 9, 10, 7, 5, 6, 4, 3]