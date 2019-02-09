#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QFileDialog>
#include <QDialogButtonBox>
#include "include/add_vhost_dialog.hpp"

AddVHostDialog::AddVHostDialog(QWidget *parent) :
	QDialog(parent)
{
	//setTitle("Add Virtual Host");

	QVBoxLayout *vbox = new QVBoxLayout;
	
	nameEdit = new QLineEdit();
	docRootEdit = new QLineEdit();
	QPushButton* browseBtn = new QPushButton("Browse");
	QHBoxLayout* browsehbox = new QHBoxLayout;
	browsehbox->addWidget(docRootEdit);
	browsehbox->addWidget(browseBtn);


	QFormLayout *formLayout = new QFormLayout;
	formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
	formLayout->addRow("Domain:", nameEdit);
	formLayout->addRow("Document Root:", browsehbox);


	vbox->addLayout(formLayout);

	QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
	vbox->addWidget(buttonBox);

	connect(browseBtn, &QPushButton::clicked, this, &AddVHostDialog::onBrowseBtnClicked);
	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
   connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
   setLayout(vbox);
}

void AddVHostDialog::onBrowseBtnClicked()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::AnyFile);
}

VHost AddVHostDialog::getVHost()
{
	VHost vh;
	vh.name = this->nameEdit->text();
	vh.docRoot = this->docRootEdit->text();
	return vh;
}

AddVHostDialog::~AddVHostDialog()
{

}