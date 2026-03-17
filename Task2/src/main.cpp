#include <iostream>
#include <locale>
#include "cafe.h"

#include <windows.h>
#include <locale>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");
    setlocale(LC_ALL, "Russian");
    
    std::cout << "============================================\n";
    std::cout << "         СИМУЛЯЦИЯ РАБОТЫ КАФЕ\n";
    std::cout << "============================================\n";
    std::cout << "Типы клиентов:\n";
    std::cout << "  - ОЧЕНЬ ГОЛОДНЫЕ  - терпение 15-20 мин\n";
    std::cout << "  - ОБЫЧНЫЕ - готовы ждать сколько угодно\n";
    std::cout << "============================================\n";
    std::cout << "Цены на блюда:\n";
    std::cout << "  - Омлет: 120 руб.\n";
    std::cout << "  - Каша: 90 руб.\n";
    std::cout << "  - Суп: 150 руб.\n";
    std::cout << "  - Второе: 180 руб.\n";
    std::cout << "  - Стейк: 250 руб.\n";
    std::cout << "  - Коктейль: 80 руб.\n";
    std::cout << "  - Чай: 50 руб.\n";
    std::cout << "  - Кофе: 80 руб.\n";
    std::cout << "============================================\n";
    std::cout << "Параметры:\n";
    std::cout << "  - Ставка повара: 200 руб/час\n";
    std::cout << "============================================\n\n";
    
    Cafe cafe;
    cafe.simulateDay();
    
    return 0;
}