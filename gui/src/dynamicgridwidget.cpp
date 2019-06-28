/*
 * This file is part of Chiaki.
 *
 * Chiaki is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Chiaki is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Chiaki.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <dynamicgridwidget.h>

#include <QGridLayout>

DynamicGridWidget::DynamicGridWidget(unsigned int item_width, QWidget *parent)
{
	layout = new QGridLayout(this);
	layout->setHorizontalSpacing(10);
	layout->setVerticalSpacing(10);
	setLayout(layout);
	this->item_width = item_width;
	columns = CalculateColumns();
}

void DynamicGridWidget::AddWidget(QWidget *widget)
{
	if(widgets.contains(widget))
		return;
	widget->setParent(this);
	widgets.append(widget);
	UpdateLayout();
}

void DynamicGridWidget::RemoveWidget(QWidget *widget)
{
	layout->removeWidget(widget);
	widget->setParent(nullptr);
	widgets.removeAll(widget);
}

unsigned int DynamicGridWidget::CalculateColumns()
{
	return (width() + layout->horizontalSpacing()) / (item_width + layout->horizontalSpacing());
}

void DynamicGridWidget::UpdateLayout()
{
	while(layout->count() > 0)
		layout->removeItem(layout->itemAt(0));

	columns = CalculateColumns();
	if(columns == 0)
		return;

	for(unsigned int i=0; i<widgets.length(); i++)
		layout->addWidget(widgets[i], i / columns, i % columns);

	setMinimumWidth(item_width);
}

void DynamicGridWidget::UpdateLayoutIfNecessary()
{
	unsigned int new_columns = CalculateColumns();
	if(new_columns != columns)
		UpdateLayout();
}
