#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QFileDialog>
#include <QDialogButtonBox>
#include "vhost_dialog.hpp"

VHostDialog::VHostDialog(QWidget *parent) :
	QDialog(parent)
{

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

	connect(browseBtn, &QPushButton::clicked, this, &VHostDialog::onBrowseBtnClicked);
	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
   connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
   setLayout(vbox);
}

void VHostDialog::onBrowseBtnClicked()
{
	QString initial = docRootEdit->text();
	QString dir = QFileDialog::getExistingDirectory(this, "Set Document Root", initial);
	if (!dir.isEmpty())
		docRootEdit->setText(dir);
}

VHost* VHostDialog::getVHost()
{
	if (vhost == nullptr){
		vhost = new VHost();
	}
	vhost->name = nameEdit->text();
	vhost->docRoot = docRootEdit->text();
	return vhost;
}

void VHostDialog::setVHost(VHost* vh)
{
	vhost = vh;
	nameEdit->setText(vh->name);
	docRootEdit->setText(vh->docRoot);
}

VHostDialog::~VHostDialog()
{
}