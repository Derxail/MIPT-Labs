#include <random>
#include <fstream>

class Rollable {
// любой объект, от которого можно вызвать .roll()
// объект Rollable, но не Dice не может сам вернуть значение при вызове .roll() без обращения к объекту Dice
public:
    Rollable() {}
    virtual unsigned roll() const = 0;
    virtual ~Rollable() {}
    virtual unsigned get_max() { return 0; }
};

class Dice: public Rollable {
// объект, который при вызове .roll() вернёт значение
public:
    Dice(unsigned max, unsigned seed):
        max(max), dstr(1, max), reng(seed) { }
    
    unsigned roll() const override {
        return dstr(reng);
    }

    unsigned get_max() override {
        return max;
    }

private:
    unsigned max;
    mutable std::uniform_int_distribution<unsigned> dstr;
    std::default_random_engine reng;
};

class ThreeDicePool: public Rollable {
public:
    ThreeDicePool(Rollable& dice1, Rollable& dice2, Rollable& dice3):
        dices {&dice1, &dice2, &dice3} { }


    unsigned roll() const override {
        return dices[0]->roll() + dices[1]->roll() + dices[2]->roll();
    }

    unsigned get_max() override {
        return dices[0]->get_max() + dices[1]->get_max() + dices[2]->get_max();
    } 
private:
    Rollable* dices[3];
};

class PenaltyDice: virtual public Rollable {
public:
    PenaltyDice(Dice& dice): dice(dice) {}

    unsigned roll() const override {
        return std::min(dice.roll(), dice.roll());
    }

    unsigned get_max() override {
        return dice.get_max();
    }
private:
    Dice& dice;
};

class BonusDice: virtual public Rollable {
public:
    BonusDice(Dice& dice): dice(dice) {}

    unsigned roll() const override {
        return std::max(dice.roll(), dice.roll());
    }

    unsigned get_max() override {
        return dice.get_max();
    }
private:
    Dice& dice;
};

class DoubleDice: public PenaltyDice, public BonusDice {
public:
    DoubleDice(Dice& dice): BonusDice(dice), PenaltyDice(dice) {}

    unsigned roll() const {
        return BonusDice::roll() + PenaltyDice::roll();
    }

    unsigned get_max() {
        return BonusDice::get_max() + PenaltyDice::get_max(); 
    }
};

class DoubleDice2: public Rollable {
public:
    DoubleDice2(Dice& dice): penalty(PenaltyDice(dice)), bonus(BonusDice(dice)) {}

    unsigned roll() const {
        return bonus.roll() + penalty.roll();
    }

    unsigned get_max() {
        return bonus.get_max() + penalty.get_max(); 
    }
private:
    PenaltyDice& penalty;
    BonusDice& bonus;
};

double expected_value(Rollable &d, unsigned number_of_rolls = 1) {
    auto accum = 0llu;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
        accum += d.roll();
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

double value_probability(unsigned value, Rollable &d, unsigned number_of_rolls = 1) {
    unsigned count = 0;
    for (unsigned i = 0; i != number_of_rolls; ++i) {
        if (d.roll() == value) ++count;
    }
    return static_cast<double>(count) / static_cast<double>(number_of_rolls);
}

void write_probability_dstr(std::ofstream& fout, Rollable &d, unsigned number_of_rolls = 1) {
    fout << "value, frequency" << std::endl;
    unsigned max_value = d.get_max();
    unsigned* count = new unsigned[max_value];
    for (unsigned i = 0; i != max_value; ++i) {
        count[i] = 0;
    }
    for (unsigned i = 0; i != number_of_rolls; ++i) {
        count[d.roll() - 1] += 1;
    }
    for (unsigned i = 0; i != max_value; ++i) {
        fout << i + 1 << ", " << static_cast<double>(count[i]) / static_cast<double>(number_of_rolls) << std::endl;
    }
}

int main() {
    Dice d100(100, 1010101);
    Dice d6_1(6, 1111111), d6_2(6, 100000), d6_3(6, 1010101);
    ThreeDicePool pool_3d6(d6_1, d6_2, d6_3);
    PenaltyDice disadv_d100(d100);
    BonusDice adv_d100(d100);
    DoubleDice double_d100(d100);
    std::ofstream expected_values_out("data/1.txt");
    expected_values_out << "d100: " << expected_value(d100, 100'000) << std::endl;
    expected_values_out << "3d6: " << expected_value(pool_3d6, 100'000) << std::endl;
    std::ofstream dstr_d100("data/dstr_d100.csv");
    std::ofstream dstr_3d6("data/dstr_3d6.csv");
    std::ofstream dstr_disadv("data/dstr_disadv.csv");
    std::ofstream dstr_adv("data/dstr_adv.csv");
    std::ofstream dstr_double("data/dstr_double.csv");
    write_probability_dstr(dstr_d100, d100, 500'000);
    write_probability_dstr(dstr_3d6, pool_3d6, 500'000);
    write_probability_dstr(dstr_disadv, disadv_d100, 500'000);
    write_probability_dstr(dstr_adv, adv_d100, 500'000);
    write_probability_dstr(dstr_double, double_d100, 500'000);
    return 0;
}

