#ifndef UNIT_H
#define UNIT_H

#include "Map.hpp"
#include <memory>
#include "Entity.hpp"

const int FACING_RIGHT = 0;
const int FACING_UP_RIGHT = 1;
const int FACING_UP = 2;
const int FACING_LEFT_UP = 3;
const int FACING_LEFT = 4;
const int FACING_DOWN_LEFT = 5;
const int FACING_DOWN = 6;
const int FACING_RIGHT_DOWN = 7;
const int FACINGS = 8;          // used to calculate width of each 'tile' for a unit given a tilset

// Sub-cell is only used for positioning, but not for remembering. Collision is
// done in another way
const int SUBCELL_UPLEFT = 1;
const int SUBCELL_UPRIGHT = 2;
const int SUBCELL_CENTER = 3;
const int SUBCELL_DOWNLEFT = 4;
const int SUBCELL_DOWNRIGHT = 5;

struct TexturePack{
    TexturePack(const sf::Texture& theUnit, const sf::Texture& theShadow, const sf::Texture& theSelected):
      unit(theUnit), shadow(theShadow), selected(theSelected) {}

    const sf::Texture& unit;
    const sf::Texture& shadow;
    const sf::Texture& selected;
};

class Unit;

struct MoveMessage : public Message{
    MoveMessage(const std::string& id, const Unit& unit):
      Message(id), unit(unit)
    {}

    const Unit& unit;
};

class Unit : public sf::Drawable, public Entity
{

  public:

    enum class Type {
      Trike,
      Quad,
      Devastator,
      Carryall,
      Frigate,
      Soldier
    };

    Unit(TexturePack pack, const sf::Vector2f& pos, Map& theMap, int theId);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void updateState(const std::vector<Unit>& units);

    void orderMove(const sf::Vector2f &target);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getCenter() const;

    void select();
    void unselect();
    bool isSelected() const;

    int getViewRange() const;

  private:
    sf::Vector2f target;            // target of interest (move/attack, etc)

    sf::Sprite sprite;
    sf::Sprite shadowSprite;
    sf::Sprite selectedSprite;      //possibly static

    int viewRange;
    int bodyFacing;
    int desiredBodyFacing;

    bool selected;

    Map& map;

    void setFacing(int facing);
    void turnBody();
    void updateMovePosition(const std::vector<Unit> &units);

    int  desiredFacing() const;
    bool hasTarget() const;
    bool shouldTurnBody() const;

    int id; //unique id for the unit
};

#endif
