#include "tdd.h"

#ifdef TEST_BONUS
static int g_delete_count = 0;

static t_list *make_node(int *value)
{
    t_list *node = malloc(sizeof(*node));

    if (!node)
        return NULL;
    node->content = value;
    node->next = NULL;
    return node;
}

static void del_count(void *content)
{
    g_delete_count++;
    free(content);
}

static int *heap_int(int value)
{
    int *p = malloc(sizeof(*p));

    if (p)
        *p = value;
    return p;
}

static void iter_double(void *content)
{
    if (content)
        *(int *)content *= 2;
}

static void *map_double(void *content)
{
    if (!content)
        return NULL;
    return heap_int(*(int *)content * 2);
}

void test_ft_lstnew(int *passed)
{
    int value = 42;
    t_list *node = ft_lstnew(&value);

    CHECK_TRUE("ft_lstnew", "allocated", node != NULL);
    if (node)
    {
        CHECK_PTR("ft_lstnew", "content", &value, node->content);
        CHECK_PTR("ft_lstnew", "next NULL", NULL, node->next);
        free(node);
    }
    node = ft_lstnew(NULL);
    CHECK_TRUE("ft_lstnew", "NULL content allocation", node != NULL);
    if (node)
    {
        CHECK_PTR("ft_lstnew", "NULL content", NULL, node->content);
        CHECK_PTR("ft_lstnew", "NULL next", NULL, node->next);
        free(node);
    }
}

void test_ft_lstadd_front(int *passed)
{
    int a = 1, b = 2;
    t_list *first = make_node(&a);
    t_list *new_head = make_node(&b);
    t_list *head = first;

    if (!first || !new_head)
    {
        CHECK_TRUE("ft_lstadd_front", "fixture allocations", 0);
        free(first);
        free(new_head);
        return;
    }
    ft_lstadd_front(&head, new_head);
    CHECK_PTR("ft_lstadd_front", "new head", new_head, head);
    CHECK_PTR("ft_lstadd_front", "old head next", first, new_head->next);
    free(first);
    free(new_head);
    new_head = make_node(&b);
    head = NULL;
    if (!new_head)
    {
        CHECK_TRUE("ft_lstadd_front", "empty fixture allocation", 0);
        return;
    }
    ft_lstadd_front(&head, new_head);
    CHECK_PTR("ft_lstadd_front", "empty list head", new_head, head);
    CHECK_PTR("ft_lstadd_front", "empty list terminator", NULL, new_head->next);
    free(new_head);
}

void test_ft_lstadd_back(int *passed)
{
    int a = 1, b = 2;
    t_list *first = make_node(&a);
    t_list *last = make_node(&b);
    t_list *head = first;

    if (!first || !last)
    {
        CHECK_TRUE("ft_lstadd_back", "fixture allocations", 0);
        free(first);
        free(last);
        return;
    }
    ft_lstadd_back(&head, last);
    CHECK_PTR("ft_lstadd_back", "head preserved", first, head);
    CHECK_PTR("ft_lstadd_back", "last appended", last, first->next);
    CHECK_PTR("ft_lstadd_back", "last terminator", NULL, last->next);
    free(first);
    free(last);
    last = make_node(&b);
    head = NULL;
    if (!last)
    {
        CHECK_TRUE("ft_lstadd_back", "empty fixture allocation", 0);
        return;
    }
    ft_lstadd_back(&head, last);
    CHECK_PTR("ft_lstadd_back", "empty list head", last, head);
    CHECK_PTR("ft_lstadd_back", "empty list terminator", NULL, last->next);
    free(last);
}

void test_ft_lstsize(int *passed)
{
    int a = 1, b = 2;
    t_list *first = make_node(&a);
    t_list *last = make_node(&b);

    CHECK_INT("ft_lstsize", "empty list", 0, ft_lstsize(NULL));
    if (!first || !last)
    {
        CHECK_TRUE("ft_lstsize", "fixture allocations", 0);
        free(first);
        free(last);
        return;
    }
    CHECK_INT("ft_lstsize", "single", 1, ft_lstsize(first));
    first->next = last;
    CHECK_INT("ft_lstsize", "two nodes", 2, ft_lstsize(first));
    free(last);
    free(first);
}

void test_ft_lstlast(int *passed)
{
    int a = 1, b = 2;
    t_list *first = make_node(&a);
    t_list *last = make_node(&b);

    CHECK_PTR("ft_lstlast", "empty", NULL, ft_lstlast(NULL));
    if (!first || !last)
    {
        CHECK_TRUE("ft_lstlast", "fixture allocations", 0);
        free(first);
        free(last);
        return;
    }
    CHECK_PTR("ft_lstlast", "single", first, ft_lstlast(first));
    first->next = last;
    CHECK_PTR("ft_lstlast", "last of two", last, ft_lstlast(first));
    free(last);
    free(first);
}

void test_ft_lstdelone(int *passed)
{
    t_list *node = make_node(heap_int(42));

    if (!node || !node->content)
    {
        CHECK_TRUE("ft_lstdelone", "fixture allocations", 0);
        if (node)
            free(node->content);
        free(node);
        return;
    }
    g_delete_count = 0;
    ft_lstdelone(node, del_count);
    CHECK_INT("ft_lstdelone", "deletion callback once", 1, g_delete_count);
}

void test_ft_lstclear(int *passed)
{
    t_list *first = make_node(heap_int(12));
    t_list *second = make_node(heap_int(34));
    t_list *head;

    if (!first || !second || !first->content || !second->content)
    {
        CHECK_TRUE("ft_lstclear", "fixture allocations", 0);
        if (first) free(first->content);
        if (second) free(second->content);
        free(first);
        free(second);
        return;
    }
    first->next = second;
    head = first;
    g_delete_count = 0;
    ft_lstclear(&head, del_count);
    CHECK_PTR("ft_lstclear", "head reset", NULL, head);
    CHECK_INT("ft_lstclear", "all content freed", 2, g_delete_count);
}

void test_ft_lstiter(int *passed)
{
    int a = 3, b = 5;
    t_list *first = make_node(&a);
    t_list *second = make_node(&b);

    if (!first || !second)
    {
        CHECK_TRUE("ft_lstiter", "fixture allocations", 0);
        free(first);
        free(second);
        return;
    }
    first->next = second;
    ft_lstiter(first, iter_double);
    CHECK_INT("ft_lstiter", "first transformed", 6, a);
    CHECK_INT("ft_lstiter", "second transformed", 10, b);
    free(second);
    free(first);
}

void test_ft_lstmap(int *passed)
{
    int a = 3, b = 5;
    t_list *first = make_node(&a);
    t_list *second = make_node(&b);
    t_list *mapped;

    if (!first || !second)
    {
        CHECK_TRUE("ft_lstmap", "fixture allocations", 0);
        free(first);
        free(second);
        return;
    }
    first->next = second;
    CHECK_PTR("ft_lstmap", "empty source", NULL,
            ft_lstmap(NULL, map_double, del_count));
    mapped = ft_lstmap(first, map_double, del_count);
    CHECK_TRUE("ft_lstmap", "mapped list", mapped != NULL);
    if (mapped)
    {
        CHECK_TRUE("ft_lstmap", "first content allocated", mapped->content != NULL);
        if (mapped->content)
            CHECK_INT("ft_lstmap", "first value", 6, *(int *)mapped->content);
        CHECK_TRUE("ft_lstmap", "second node", mapped->next != NULL);
        if (mapped->next)
        {
            CHECK_TRUE("ft_lstmap", "second content allocated", mapped->next->content != NULL);
            if (mapped->next->content)
                CHECK_INT("ft_lstmap", "second value", 10, *(int *)mapped->next->content);
            CHECK_PTR("ft_lstmap", "list terminator", NULL, mapped->next->next);
        }
        CHECK_TRUE("ft_lstmap", "independent nodes", mapped != first);
        ft_lstclear(&mapped, del_count);
    }
    CHECK_INT("ft_lstmap", "original first unchanged", 3, a);
    CHECK_INT("ft_lstmap", "original second unchanged", 5, b);
    free(second);
    free(first);
}
#endif
