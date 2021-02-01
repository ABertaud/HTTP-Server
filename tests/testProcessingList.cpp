/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** testProcessingList.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "processingList.hpp"

Test(processSimpleAdd, processingList)
{
    processingList processList;

    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::SSL);

    cr_assert_eq(processList.getCurrentType(), moduleType::SSL);
}

Test(processRemoveAdd, processingList)
{
    processingList processList;

    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::SSL);

    cr_assert_eq(processList.getCurrentType(), moduleType::SSL);
    processList.remove();
    cr_assert_eq(processList.getCurrentType(), moduleType::PHPCGI);
}

Test(processAddAtPos, processingList)
{
    processingList processList;

    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::SSL, 1);

    processList.remove();
    cr_assert_eq(processList.getCurrentType(), moduleType::SSL);
}

Test(processRemoveAtPos, processingList)
{
    processingList processList;

    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::SSL, 1);

    processList.remove(1);
    processList.remove();
    cr_assert_eq(processList.getCurrentType(), moduleType::PHPCGI);
}

Test(processAddHigher, processingList)
{
    processingList processList;

    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::PHPCGI);
    processList.add(moduleType::SSL, 3);

    processList.remove();
    processList.remove();
    cr_assert_eq(processList.getCurrentType(), moduleType::SSL);
}

Test(processRemoveHigher, processingList)
{
    processingList processList;

    processList.add(moduleType::PHPCGI);

    processList.remove(10);
    cr_assert_eq(processList.getCurrentType(), moduleType::NONE);
}