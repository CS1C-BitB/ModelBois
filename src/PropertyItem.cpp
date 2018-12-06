#include "PropertyItem.h"

#include "MainWindow.h"
#include "PosButton.h"
#include "Shapes.h"

using namespace std::placeholders;

/******************************************************************************
 * 
 * Shape specialization
 * 
 *****************************************************************************/

PropertyItem<Shape>::PropertyItem(QTreeWidgetItem* parent, Shape& s)
    : QTreeWidgetItem(parent, PropNone),
      name{QString("ID: %1; Type: %2").arg(s.getID()).arg(SHAPE_NAMES[s.getType()])}
{
	new PropertyItem<QPoint>(
	            this,
	            "Position",
	            std::bind(&Shape::getPos, &s),
	            [&s](QPoint p) { s.setPos(p); }
	);
	if (s.getType() != TextType) {
		new PropertyItem<QPen>(
			this,
			"Line",
			std::bind(&Shape::getPen, &s),
			std::bind(&Shape::setPen, &s, _1)
		);
	}
	if (Shape::hasFill(s.getType())) {
		new PropertyItem<QBrush>(
			this,
			"Fill",
			std::bind(&Shape::getBrush, &s),
			std::bind(&Shape::setBrush, &s, _1)
		);
	}
	
#define TRY_CAST(type, var) auto* var = dynamic_cast<type*>(&s)
	
	if (TRY_CAST(Ellipse, ellipse)) {
		new PropertyItem<QRect>(this,
		                        "Ellipse",
		                        std::bind(&Ellipse::getRect, ellipse),
		                        std::bind(&Ellipse::setRect, ellipse, _1)
		);
	}
	else if (TRY_CAST(Line, line)) {
		new PropertyItem<Line>(this, *line);
	}
	else if (TRY_CAST(Polygon, poly)) {
		new PropertyItem<Polygon>(this, *poly);
	}
	else if (TRY_CAST(PolyLine, poly)) {
		new PropertyItem<PolyLine>(this, *poly);
	}
	else if (TRY_CAST(Rectangle, rect)) {
		new PropertyItem<QRect>(this,
		                        "Rectangle",
		                        std::bind(&Rectangle::getRect, rect),
		                        std::bind(&Rectangle::setRect, rect, _1)
		);
	}
	else if (TRY_CAST(Text, text)) {
		new PropertyItem<Text>(this, *text);
	}
#undef TRY_CAST
	
	treeWidget()->setCurrentItem(this);
}

/******************************************************************************
 * 
 * Line specialization
 * 
 *****************************************************************************/

PropertyItem<Line>::PropertyItem(QTreeWidgetItem* parent, Line& line)
    : QTreeWidgetItem(parent, PropNone), name{"Line"}
{
	new PropertyItem<QPoint>(
	            this,
	            "Start",
	            std::bind(&Line::getStart, &line),
	            std::bind(&Line::setStart, &line, _1)
	);
	new PropertyItem<QPoint>(
	            this,
	            "End",
	            std::bind(&Line::getEnd, &line),
	            std::bind(&Line::setEnd, &line, _1)
	);
}

/******************************************************************************
 * 
 * Polygon specialization
 * 
 *****************************************************************************/

PropertyItem<Polygon>::PropertyItem(QTreeWidgetItem* parent, Polygon& poly)
    : QTreeWidgetItem(parent, PropNone), name{"Polygon"}
{
	
	new PropertyItem<QList<QPoint>>(
	            this,
	            "Vertices",
	            std::bind(&Polygon::getCount, &poly),
	            std::bind(&Polygon::getPoint, &poly, _1),
	            std::bind(&Polygon::setPoint, &poly, _1, _2),
	            std::bind(&Polygon::insert, &poly, _1, _2),
	            std::bind(&Polygon::erase, &poly, _1)
	);
}

/******************************************************************************
 * 
 * PolyLine specialization
 * 
 *****************************************************************************/

PropertyItem<PolyLine>::PropertyItem(QTreeWidgetItem* parent, PolyLine& poly)
    : QTreeWidgetItem(parent, PropNone), name{"PolyLine"}
{
	
	new PropertyItem<QList<QPoint>>(
	            this,
	            "Vertices",
	            std::bind(&PolyLine::getCount, &poly),
	            std::bind(&PolyLine::getPoint, &poly, _1),
	            std::bind(&PolyLine::setPoint, &poly, _1, _2),
	            std::bind(&PolyLine::insert, &poly, _1, _2),
	            std::bind(&PolyLine::erase, &poly, _1)
	);
}

/******************************************************************************
 * 
 * Text specialization
 * 
 *****************************************************************************/

PropertyItem<Text>::PropertyItem(QTreeWidgetItem* parent, Text& text)
    : QTreeWidgetItem(parent, PropNone), name{"Text"}
{
	new PropertyItem<QString>(
	            this,
	            "Text",
	            std::bind(&Text::getString, &text),
	            std::bind(&Text::setString, &text, _1),
	            PropString
	);
	new PropertyItem<QString>(
	            this,
	            "Color",
	            ([&text]() { return COLOR_NAMES.key(text.getPen().color()); }),
	            ([&text](QString s) { QPen p = text.getPen(); p.setColor(COLOR_NAMES[s]); text.setPen(p); }),
	            PropColor
	);
	new PropertyItem<QFont>(
	            this,
	            "Font",
	            std::bind(&Text::getFont, &text),
	            std::bind(&Text::setFont, &text, _1)
	);
	new PropertyItem<QRect>(
	            this,
	            "Box",
	            std::bind(&Text::getRect, &text),
	            std::bind(&Text::setRect, &text, _1)
	);
	new PropertyItem<QString>(
	            this,
	            "Alignment",
	            ([&text]() { return ALIGNMENT_NAMES[text.getAlign()]; }),
	            ([&text](QString s) { text.setAlign(ALIGNMENT_NAMES.key(s)); }),
	            PropAlignment
	);
}

/******************************************************************************
 * 
 * QPoint specialization
 * 
 *****************************************************************************/

void Disconnect(MainWindow* window, QTreeWidget* tree)
{
	QObject::disconnect(window, &MainWindow::onCanvasClick, nullptr, nullptr);
	QObject::disconnect(tree, &QTreeWidget::currentItemChanged, nullptr, nullptr);
	window->SetCanvasCursor(Qt::ArrowCursor);
	window->SetStatusText("");
}

PropertyItem<QPoint>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
    : QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new PropertyItem<int>(
	            this,
	            "X",
	            [this]() -> int { return getter().x(); },
	            [this](int x) { setter(QPoint{x, getter().y()}); }
	);
	new PropertyItem<int>(
	            this,
	            "Y",
	            [this]() -> int { return getter().y(); },
	            [this](int y) { setter(QPoint{getter().x(), y}); }
	);
	
	auto* window = dynamic_cast<MainWindow*>(treeWidget()->window());
	
	auto* buttonWidget = new PosButton();
	QObject::connect(buttonWidget, &PosButton::clicked, [this, window]() {
		treeWidget()->setCurrentItem(this);
		// Set pointer
		window->SetCanvasCursor(Qt::CrossCursor);
		window->SetStatusText("Click to set position");
		// Set setter
		QObject::connect(window, &MainWindow::onCanvasClick, [this, window](int x, int y) {
			setter(QPoint{x, y});
			emitDataChanged();
			// Unset setter
			Disconnect(window, treeWidget());
		});
		QObject::connect(treeWidget(), &QTreeWidget::currentItemChanged, std::bind(&Disconnect, window, treeWidget()));
	});
	treeWidget()->setItemWidget(this, 1, buttonWidget);
}

QVariant PropertyItem<QPoint>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		else {
			QPoint p = getter();
			return QString{"(%1, %2)"}.arg(p.x()).arg(p.y());
		}
	}
	
	return QVariant{};
}

/******************************************************************************
 * 
 * QPoint list specialization
 * 
 *****************************************************************************/

PropertyItem<QList<QPoint>>::PropertyItem(QTreeWidgetItem* parent, QString name, get_size_t get_size_in, get_item_t get_item_in, set_item_t set_item_in, insert_t insert_in, erase_t erase_in)
    : QTreeWidgetItem(parent, PropNone),
      name{std::move(name)},
      get_size{std::move(get_size_in)},
      get_item{std::move(get_item_in)},
      set_item{std::move(set_item_in)},
      insert{std::move(insert_in)},
      erase{std::move(erase_in)}
{
	size_t i = 0, count = get_size();
	for (; i < count; ++i) {
		new PropertyItem<QPoint>(
		            this,
		            QString{"[%1]"}.arg(i),
		            std::bind(get_item, i),
		            std::bind(set_item, i, std::placeholders::_1)
		);
	}
	
	auto* buttons = new ListButtons();
	buttons->setRemoveEnabled(count != 0);
	QObject::connect(buttons, &ListButtons::add, std::bind(&PropertyItem<QList<QPoint>>::add, this));
	QObject::connect(buttons, &ListButtons::remove, std::bind(&PropertyItem<QList<QPoint>>::remove, this));
	treeWidget()->setItemWidget(this, 1, buttons);
}

void PropertyItem<QList<QPoint>>::add()
{
	auto* window = dynamic_cast<MainWindow*>(treeWidget()->window());
	treeWidget()->setCurrentItem(this);
	
	// Set pointer
	window->SetCanvasCursor(Qt::CrossCursor);
	window->SetStatusText("Click to add points");
	
	// Set setter
	QObject::connect(window, &MainWindow::onCanvasClick, [this](int x, int y) {
		size_t i = get_size();
		insert(i, QPoint{x, y});
		auto* prop = new PropertyItem<QPoint>(
		            this,
		            QString{"[%1]"}.arg(i),
		            std::bind(get_item, i),
		            std::bind(set_item, i, _1)
		);
		treeWidget()->expandItem(prop);
		emitDataChanged();
		dynamic_cast<ListButtons*>(treeWidget()->itemWidget(this, 1))->setRemoveEnabled(true);
	});
	QObject::connect(treeWidget(), &QTreeWidget::currentItemChanged, std::bind(&Disconnect, window, treeWidget()));
}

void PropertyItem<QList<QPoint>>::remove()
{
	auto* window = dynamic_cast<MainWindow*>(treeWidget()->window());
	
	Disconnect(window, treeWidget());
	
	size_t i = get_size() - 1;
	erase(i);
	removeChild(child(static_cast<int>(i)));
	dynamic_cast<ListButtons*>(treeWidget()->itemWidget(this, 1))->setRemoveEnabled(i != 0);
	emitDataChanged();
}

QVariant PropertyItem<QList<QPoint>>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		else {
			return QString{"Size: %1"}.arg(get_size());
		}
	}
	
	return QVariant{};
}

/******************************************************************************
 * 
 * QRect specialization
 * 
 *****************************************************************************/

PropertyItem<QRect>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
    : QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new PropertyItem<int>(
	            this,
	            "X",
	            [this]() -> int { return getter().left(); },
	            [this](int x) { auto v = getter(); v.moveLeft(x); setter(v); }
	);
	new PropertyItem<int>(
	            this,
	            "Y",
	            [this]() -> int { return getter().top(); },
	            [this](int x) { auto v = getter(); v.moveTop(x); setter(v); }
	);
	new PropertyItem<int>(
	            this,
	            "Width",
	            [this]() -> int { return getter().width(); },
	            [this](int x) { auto v = getter(); v.setWidth(x); setter(v); }
	);
	new PropertyItem<int>(
	            this,
	            "Height",
	            [this]() -> int { return getter().height(); },
	            [this](int x) { auto v = getter(); v.setHeight(x); setter(v); }
	);
}

QVariant PropertyItem<QRect>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		else {
			QRect r = getter();
			return QString{"[(%1, %2), %3x%4]"}.arg(r.x()).arg(r.y()).arg(r.width()).arg(r.height());
		}
	}
	
	return QVariant{};
}

/******************************************************************************
 * 
 * QPen specialization
 * 
 *****************************************************************************/

PropertyItem<QPen>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
    : QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new PropertyItem<int>(
	            this,
	            "Width",
	            [this]() { return getter().width(); },
	            [this](int w) { auto v = getter(); v.setWidth(w); setter(v); }
	);
	new PropertyItem<QString>(
	            this,
	            "Color",
	            [this]() { return COLOR_NAMES.key(getter().color()); },
	            [this](QString s) { auto v = getter(); v.setColor(COLOR_NAMES[s]); setter(v); },
	            PropColor
	);
	new PropertyItem<QString>(
	            this,
	            "Style",
	            [this]() { return PEN_STYLE_NAMES[getter().style()]; },
	            [this](QString s) { auto v = getter(); v.setStyle(PEN_STYLE_NAMES.key(s)); setter(v); },
	            PropPenStyle
	);
	new PropertyItem<QString>(
	            this,
	            "Cap Style",
	            [this]() { return PEN_CAP_STYLE_NAMES[getter().capStyle()]; },
	            [this](QString s) { auto v = getter(); v.setCapStyle(PEN_CAP_STYLE_NAMES.key(s)); setter(v); },
	            PropPenCapStyle
	);
	new PropertyItem<QString>(
	            this,
	            "Join Style",
	            [this]() { return PEN_JOIN_STYLE_NAMES[getter().joinStyle()]; },
	            [this](QString s) { auto v = getter(); v.setJoinStyle(PEN_JOIN_STYLE_NAMES.key(s)); setter(v); },
	            PropPenJoinStyle
	);
}

QVariant PropertyItem<QPen>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		break;
	}
	
	return QVariant{};
}

/******************************************************************************
 * 
 * QBrush specialization
 * 
 *****************************************************************************/

PropertyItem<QBrush>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
    : QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new PropertyItem<QString>(
	            this,
	            "Color",
	            [this]() { return COLOR_NAMES.key(getter().color()); },
	            [this](QString s) { auto v = getter(); v.setColor(COLOR_NAMES[s]); setter(v); },
	            PropColor
	);
	new PropertyItem<QString>(
	            this,
	            "Style",
	            [this]() { return BRUSH_STYLE_NAMES[getter().style()]; },
	            [this](QString s) { auto v = getter(); v.setStyle(BRUSH_STYLE_NAMES.key(s)); setter(v); },
	            PropBrushStyle
	);
}

QVariant PropertyItem<QBrush>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		break;
	}
	
	return QVariant{};
}

/******************************************************************************
 * 
 * QFont specialization
 * 
 *****************************************************************************/

PropertyItem<QFont>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
    : QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new PropertyItem<QString>(
	            this,
	            "Family",
	            ([this]() { return getter().family(); }),
	            ([this](QString s) { QFont f = getter(); f.setFamily(s); setter(f); }),
	            PropFont
	);
	new PropertyItem<int>(
	            this,
	            "Size",
	            ([this]() { return getter().pointSize(); }),
	            ([this](int s) { QFont f = getter(); f.setPointSize(s); setter(f); }),
	            PropInt
	);
	new PropertyItem<QString>(
	            this,
	            "Style",
	            ([this]() { return FONT_STYLE_NAMES[getter().style()]; }),
	            ([this](QString s) { QFont f = getter(); f.setStyle(FONT_STYLE_NAMES.key(s)); setter(f); }),
	            PropFontStyle
	);
	new PropertyItem<QString>(
	            this,
	            "Weight",
	            ([this]() { return FONT_WEIGHT_NAMES[static_cast<QFont::Weight>(getter().weight())]; }),
	            ([this](QString s) { QFont f = getter(); f.setWeight(FONT_WEIGHT_NAMES.key(s)); setter(f); }),
	            PropFontWight
	);
}

QVariant PropertyItem<QFont>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		break;
	}
	
	return QVariant{};
}

