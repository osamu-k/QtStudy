#include "mainwidget.h"

#include <mach/host_info.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#include <mach/task.h>

#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    m_labelMemSize = new QLabel;
    m_labelMaxMem = new QLabel;
    m_labelPageSize = new QLabel;
    m_labelUsed = new QLabel;
    m_labelFree = new QLabel;
    m_labelTotal = new QLabel;
    m_labelVirtual = new QLabel;
    m_labelResident = new QLabel;

    QPushButton *buttonAlloc = new QPushButton("Alloc");
    QPushButton *buttonFree = new QPushButton("Free");
    QPushButton *buttonRefresh = new QPushButton("Refresh");

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow( new QLabel("Memory Size:"), m_labelMemSize );
    formLayout->addRow( new QLabel("Max Memory:"), m_labelMaxMem );
    formLayout->addRow( new QLabel("Page Size:"), m_labelPageSize );
    formLayout->addRow( new QLabel("Used:"), m_labelUsed );
    formLayout->addRow( new QLabel("Free:"), m_labelFree );
    formLayout->addRow( new QLabel("Total:"), m_labelTotal );
    formLayout->addRow( new QLabel("Virtual:"), m_labelVirtual );
    formLayout->addRow( new QLabel("Resident:"), m_labelResident );

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->addLayout( formLayout );
    vBoxLayout->addWidget( buttonAlloc );
    vBoxLayout->addWidget( buttonFree );
    vBoxLayout->addWidget( buttonRefresh );

    setLayout( vBoxLayout );

    connect( buttonAlloc, SIGNAL(clicked(bool)),
             this, SLOT(allocMemory()) );
    connect( buttonFree, SIGNAL(clicked(bool)),
             this, SLOT(freeMemory()) );
    connect( buttonRefresh, SIGNAL(clicked(bool)),
             this, SLOT(refreshDisplay()) );

    refreshDisplay();
}

MainWidget::~MainWidget()
{

}

void MainWidget::allocMemory()
{
    char *mem = new char[4096*1024];
    m_allocStack.push(mem);
}

void MainWidget::freeMemory()
{
    if( ! m_allocStack.empty() ){
        char *mem = m_allocStack.pop();
        delete[] mem;
    }
}

void MainWidget::refreshDisplay()
{
    mach_port_t host_port = mach_host_self();

    struct host_basic_info basic_info;
    mach_msg_type_number_t basic_info_count = HOST_BASIC_INFO_COUNT;
    host_info(host_port, HOST_BASIC_INFO, (host_info_t)&basic_info, &basic_info_count);

    natural_t mem_size = basic_info.memory_size;
    uint64_t max_mem = basic_info.max_mem;

    mach_msg_type_number_t host_size;
    vm_size_t pagesize;

    host_port = mach_host_self();
    host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    host_page_size(host_port, &pagesize);

    vm_statistics_data_t vm_stat;

    kern_return_t ret = host_statistics(
                            host_port,
                            HOST_VM_INFO,
                            (host_info_t)&vm_stat,
                            &host_size);

    if( ret != KERN_SUCCESS ){
        return;
    }

    natural_t mem_used = (vm_stat.active_count +
                          vm_stat.inactive_count +
                          vm_stat.wire_count) * pagesize;

    natural_t mem_free = vm_stat.free_count * pagesize;
    natural_t mem_total = mem_used + mem_free;

    task_basic_info info;
    mach_msg_type_number_t size = sizeof( info );
    ret = task_info( mach_task_self(),
                     TASK_BASIC_INFO,
                     (task_info_t)&info,
                     &size );
    if ( ret != KERN_SUCCESS ) {
        return;
    }

    natural_t mem_virtual = info.virtual_size;
    natural_t mem_resident = info.resident_size;

    m_labelMemSize->setText( QString::number(mem_size) );
    m_labelMaxMem->setText( QString::number(max_mem) );
    m_labelPageSize->setText( QString::number(pagesize) );
    m_labelUsed->setText( QString::number(mem_used) );
    m_labelFree->setText( QString::number(mem_free) );
    m_labelTotal->setText( QString::number(mem_total) );
    m_labelVirtual->setText( QString::number(mem_virtual) );
    m_labelResident->setText( QString::number(mem_resident) );
}
