#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Herbivore
{
protected:
    double weight;
    bool life;
public:
    Herbivore(double mass, bool alive) : weight(mass), life(alive)
    {
    }
    virtual ~Herbivore()
    {
    }
    virtual string GetName() = 0;
    virtual void EatGrass() = 0;
    bool GetLife()
    {
        return life;
    }
    void SetLife(bool alive)
    {
        life = alive;
    }
    double GetWeight()
    {
        return weight;
    }
    void SetWeight(double mass)
    {
        weight = mass;
    }
};

class Wildebeest : public Herbivore
{
public:
    Wildebeest() : Herbivore(100, true)
    {
    }
    Wildebeest(double mass, bool alive) : Herbivore(mass, alive)
    {
    }
    string GetName() override
    {
        return "Wildebeest";
    }
    void EatGrass() override
    {
        if (life)
        {
            weight += 10;
            cout << GetName() << " eats grass. Weight: " << weight << endl;
        }
    }
};

class Bison : public Herbivore
{
public:
    Bison() : Herbivore(500, true)
    {
    }
    Bison(double mass, bool alive) : Herbivore(mass, alive)
    {
    }
    string GetName() override
    {
        return "Bison";
    }
    void EatGrass() override
    {
        if (life)
        {
            weight += 10;
            cout << GetName() << " eats grass. Weight: " << weight << endl;
        }
    }
};

class Moose : public Herbivore
{
public:
    Moose() : Herbivore(400, true)
    {
    }
    Moose(double mass, bool alive) : Herbivore(mass, alive)
    {
    }
    string GetName() override
    {
        return "Moose";
    }
    void EatGrass() override
    {
        if (life)
        {
            weight += 10;
            cout << GetName() << " eats grass. Weight: " << weight << endl;
        }
    }
};

class Carnivore
{
protected:
    double power;
public:
    Carnivore(double strength) : power(strength)
    {
    }
    virtual ~Carnivore()
    {
    }
    virtual void Eat(Herbivore* prey) = 0;
};

class Lion : public Carnivore
{
public:
    Lion() : Carnivore(300)
    {
    }
    Lion(double strength) : Carnivore(strength)
    {
    }
    void Eat(Herbivore* prey) override
    {
        if (prey->GetName() != "Wildebeest")
        {
            return;
        }
        if (prey->GetLife() == false)
        {
            return;
        }
        if (power >= prey->GetWeight())
        {
            power += 10;
        }
        else
        {
            power -= 10;
        }
        prey->SetLife(false);
        cout << "Lion power: " << power << endl;
    }
};

class Wolf : public Carnivore
{
public:
    Wolf() : Carnivore(200)
    {
    }
    Wolf(double strength) : Carnivore(strength)
    {
    }
    void Eat(Herbivore* prey) override
    {
        if (prey->GetName() != "Bison")
        {
            return;
        }
        if (prey->GetLife() == false)
        {
            return;
        }
        if (power >= prey->GetWeight())
        {
            power += 10;
        }
        else
        {
            power -= 10;
        }
        prey->SetLife(false);
        cout << "Wolf power: " << power << endl;
    }
};

class EuWolf : public Carnivore
{
public:
    EuWolf() : Carnivore(250)
    {
    }
    EuWolf(double strength) : Carnivore(strength)
    {
    }
    void Eat(Herbivore* prey) override
    {
        if (prey->GetName() != "Moose")
        {
            return;
        }
        if (prey->GetLife() == false)
        {
            return;
        }
        if (power >= prey->GetWeight())
        {
            power += 10;
        }
        else
        {
            power -= 10;
        }
        prey->SetLife(false);
        cout << "European wolf power: " << power << endl;
    }
};

class Continent
{
protected:
    vector<Herbivore*> plantEaters;
    vector<Carnivore*> predators;
public:
    virtual ~Continent()
    {
        for (int i = 0; i < plantEaters.size(); i++)
        {
            delete plantEaters[i];
        }
        for (int i = 0; i < predators.size(); i++)
        {
            delete predators[i];
        }
    }
    virtual void CreateCarnivore() = 0;
    virtual void CreateHerbivore() = 0;
    vector<Carnivore*>& GetCarnlist()
    {
        return predators;
    }
    vector<Herbivore*>& GetHerblist()
    {
        return plantEaters;
    }
    void CreateAnimals()
    {
        CreateHerbivore();
        CreateCarnivore();
    }
};

class Europe : public Continent
{
public:
    void CreateCarnivore() override
    {
        predators.push_back(new EuWolf());
    }
    void CreateHerbivore() override
    {
        plantEaters.push_back(new Moose());
    }
};

class Africa : public Continent
{
public:
    void CreateCarnivore() override
    {
        predators.push_back(new Lion());
    }
    void CreateHerbivore() override
    {
        plantEaters.push_back(new Wildebeest());
    }
};

class NorthAmerica : public Continent
{
public:
    void CreateCarnivore() override
    {
        predators.push_back(new Wolf());
    }
    void CreateHerbivore() override
    {
        plantEaters.push_back(new Bison());
    }
};

class AnimalWorld
{
public:
    void MealsCarn(const vector<Herbivore*>& food, const vector<Carnivore*>& hunters)
    {
        auto foodIt = food.begin();
        for (auto hunterIt = hunters.begin(); hunterIt != hunters.end() && foodIt != food.end(); hunterIt++)
        {
            (*hunterIt)->Eat(*foodIt);
            foodIt++;
        }
    }
    void MealsHerb(const vector<Herbivore*>& animals)
    {
        for (auto ptr = animals.begin(); ptr != animals.end(); ptr++)
        {
            (*ptr)->EatGrass();
        }
    }
};

int main()
{
    Africa africa;
    NorthAmerica america;
    Europe europe;
    AnimalWorld world;

    for (int i = 0; i < 3; i++)
    {
        africa.CreateAnimals();
        america.CreateAnimals();
        europe.CreateAnimals();
    }

    cout << "Herbivores eating:" << endl;
    world.MealsHerb(africa.GetHerblist());
    world.MealsHerb(america.GetHerblist());
    world.MealsHerb(europe.GetHerblist());

    cout << "\nCarnivores eating:" << endl;
    world.MealsCarn(africa.GetHerblist(), africa.GetCarnlist());
    world.MealsCarn(america.GetHerblist(), america.GetCarnlist());
    world.MealsCarn(europe.GetHerblist(), europe.GetCarnlist());
}
