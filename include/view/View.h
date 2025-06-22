#ifndef VIEW_H
#define VIEW_H

class View {
public:
    virtual ~View() = default;
    virtual void render() = 0;
};

#endif