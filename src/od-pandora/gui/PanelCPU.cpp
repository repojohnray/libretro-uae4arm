#include <guichan.hpp>
#include <SDL/SDL_ttf.h>
#include <guichan/sdl.hpp>
#include "sdltruetypefont.hpp"
#include "SelectorEntry.hpp"
#include "UaeRadioButton.hpp"
#include "UaeCheckBox.hpp"

#include "sysconfig.h"
#include "sysdeps.h"
#include "config.h"
#include "options.h"
#include "uae.h"
#include "gui.h"
#include "target.h"
#include "gui_handling.h"


static gcn::Window *grpCPU;
static gcn::UaeRadioButton* optCPU68000;
static gcn::UaeRadioButton* optCPU68010;
static gcn::UaeRadioButton* optCPU68EC020;
static gcn::UaeRadioButton* optCPU68020;
static gcn::UaeRadioButton* optCPU68040;
static gcn::UaeCheckBox* chkCPUCompatible;
static gcn::UaeCheckBox* chkJIT;
static gcn::Window *grpFPU;
static gcn::UaeRadioButton* optFPUnone;
static gcn::UaeRadioButton* optFPU68881;
static gcn::UaeRadioButton* optFPU68882;
static gcn::Window *grpCPUSpeed;
static gcn::UaeRadioButton* opt7Mhz;
static gcn::UaeRadioButton* opt14Mhz;
static gcn::UaeRadioButton* opt28Mhz;
static gcn::UaeRadioButton* optFastest;


class CPUButtonActionListener : public gcn::ActionListener
{
  public:
    void action(const gcn::ActionEvent& actionEvent)
    {
	    if (actionEvent.getSource() == optCPU68000)
	    {
  		  changed_prefs.cpu_level = 0;
  		  changed_prefs.address_space_24 = true;
  		  changed_prefs.z3fastmem_size = 0;
  		  changed_prefs.gfxmem_size = 0;
      }
      else if (actionEvent.getSource() == optCPU68010)
      {
	      changed_prefs.cpu_level = 1;
  		  changed_prefs.address_space_24 = true;
  		  changed_prefs.z3fastmem_size = 0;
  		  changed_prefs.gfxmem_size = 0;
  		  changed_prefs.cpu_compatible = 0;
      }
      else if (actionEvent.getSource() == optCPU68EC020)
      {
	      changed_prefs.cpu_level = 2;
  		  changed_prefs.address_space_24 = true;
  		  changed_prefs.z3fastmem_size = 0;
  		  changed_prefs.gfxmem_size = 0;
  		  changed_prefs.cpu_compatible = 0;
      }
      else if (actionEvent.getSource() == optCPU68020)
      {
	      if(optFPU68881->isSelected())
	        changed_prefs.cpu_level = 3; // with 68881
	      else
	        changed_prefs.cpu_level = 2; // no fpu
  		  changed_prefs.address_space_24 = false;
  		  changed_prefs.cpu_compatible = 0;
      }
      else if (actionEvent.getSource() == optCPU68040)
      {
	      changed_prefs.cpu_level = 4;
  		  changed_prefs.address_space_24 = false;
  		  changed_prefs.cpu_compatible = 0;
      }
	    RefreshPanelCPU();
	    RefreshPanelRAM();
    }
};
static CPUButtonActionListener* cpuButtonActionListener;


class FPUButtonActionListener : public gcn::ActionListener
{
  public:
    void action(const gcn::ActionEvent& actionEvent)
    {
	    if (actionEvent.getSource() == optFPUnone)
  		{
  		  if(changed_prefs.cpu_level == 3)
  		    changed_prefs.cpu_level = 2;
  		}
      else if(actionEvent.getSource() == optFPU68881)
  		{
  		  if(changed_prefs.cpu_level == 2)
  		    changed_prefs.cpu_level = 3;
  		}
	    else
	      ;
    }
};
static FPUButtonActionListener* fpuButtonActionListener;


class CPUSpeedButtonActionListener : public gcn::ActionListener
{
  public:
    void action(const gcn::ActionEvent& actionEvent)
    {
	    if (actionEvent.getSource() == opt7Mhz)
      	changed_prefs.m68k_speed = M68K_SPEED_7MHZ_CYCLES;
      else if (actionEvent.getSource() == opt14Mhz)
	      changed_prefs.m68k_speed = M68K_SPEED_14MHZ_CYCLES;
      else if (actionEvent.getSource() == opt28Mhz)
	      changed_prefs.m68k_speed = M68K_SPEED_25MHZ_CYCLES;
      else if (actionEvent.getSource() == optFastest)
	      changed_prefs.m68k_speed = -1;
    }
};
static CPUSpeedButtonActionListener* cpuSpeedButtonActionListener;


class CPUCompActionListener : public gcn::ActionListener
{
  public:
    void action(const gcn::ActionEvent& actionEvent)
    {
	    if (chkCPUCompatible->isSelected())
      {
	      changed_prefs.cpu_compatible = 1;
	      changed_prefs.cachesize = 0;
      }
      else
      {
	      changed_prefs.cpu_compatible = 0;
      }
      RefreshPanelCPU();
    }
};
static CPUCompActionListener* cpuCompActionListener;


class JITActionListener : public gcn::ActionListener
{
  public:
    void action(const gcn::ActionEvent& actionEvent)
    {
	    if (chkJIT->isSelected())
      {
	      changed_prefs.cpu_compatible = 0;
	      changed_prefs.cachesize = DEFAULT_JIT_CACHE_SIZE;
      }
      else
      {
	      changed_prefs.cachesize = 0;
      }
      RefreshPanelCPU();
    }
};
static JITActionListener* jitActionListener;


void InitPanelCPU(const struct _ConfigCategory& category)
{
  cpuButtonActionListener = new CPUButtonActionListener();
  cpuCompActionListener = new CPUCompActionListener();
  jitActionListener = new JITActionListener();
  
	optCPU68000 = new gcn::UaeRadioButton("68000", "radiocpugroup");
	optCPU68000->addActionListener(cpuButtonActionListener);
	optCPU68010 = new gcn::UaeRadioButton("68010", "radiocpugroup");
	optCPU68010->addActionListener(cpuButtonActionListener);
	optCPU68EC020 = new gcn::UaeRadioButton("68EC020", "radiocpugroup");
	optCPU68EC020->addActionListener(cpuButtonActionListener);
	optCPU68020 = new gcn::UaeRadioButton("68020", "radiocpugroup");
	optCPU68020->addActionListener(cpuButtonActionListener);
	optCPU68040 = new gcn::UaeRadioButton("68040", "radiocpugroup");
	optCPU68040->addActionListener(cpuButtonActionListener);
	
	chkCPUCompatible = new gcn::UaeCheckBox("More compatible", true);
	chkCPUCompatible->setId("CPUComp");
  chkCPUCompatible->addActionListener(cpuCompActionListener);

	chkJIT = new gcn::UaeCheckBox("JIT", true);
	chkJIT->setId("JIT");
  chkJIT->addActionListener(jitActionListener);
	
	grpCPU = new gcn::Window("CPU");
	grpCPU->setPosition(DISTANCE_BORDER, DISTANCE_BORDER);
	grpCPU->add(optCPU68000, 5, 10);
	grpCPU->add(optCPU68010, 5, 40);
	grpCPU->add(optCPU68EC020, 5, 70);
	grpCPU->add(optCPU68020, 5, 100);
	grpCPU->add(optCPU68040, 5, 130);
	grpCPU->add(chkCPUCompatible, 5, 170);
	grpCPU->add(chkJIT, 5, 200);
	grpCPU->setMovable(false);
	grpCPU->setSize(160, 245);
  grpCPU->setBaseColor(gui_baseCol);
  
  category.panel->add(grpCPU);

  fpuButtonActionListener = new FPUButtonActionListener();

	optFPUnone = new gcn::UaeRadioButton("None", "radiofpugroup");
	optFPUnone->setId("FPUnone");
	optFPUnone->addActionListener(fpuButtonActionListener);

	optFPU68881 = new gcn::UaeRadioButton("68881", "radiofpugroup");
	optFPU68881->addActionListener(fpuButtonActionListener);
  
	optFPU68882 = new gcn::UaeRadioButton("68882", "radiofpugroup");
	optFPU68882->addActionListener(fpuButtonActionListener);

	grpFPU = new gcn::Window("FPU");
	grpFPU->setPosition(DISTANCE_BORDER, DISTANCE_BORDER + grpCPU->getHeight() + DISTANCE_NEXT_Y);
	grpFPU->add(optFPUnone,  5, 10);
	grpFPU->add(optFPU68881, 5, 40);
//	grpFPU->add(optFPU68882, 5, 70);
	grpFPU->setMovable(false);
	grpFPU->setSize(grpCPU->getWidth(), 115);
  grpFPU->setBaseColor(gui_baseCol);
  
  category.panel->add(grpFPU);

  cpuSpeedButtonActionListener = new CPUSpeedButtonActionListener();

	opt7Mhz = new gcn::UaeRadioButton("7 Mhz", "radiocpuspeedgroup");
	opt7Mhz->addActionListener(cpuSpeedButtonActionListener);

	opt14Mhz = new gcn::UaeRadioButton("14 Mhz", "radiocpuspeedgroup");
	opt14Mhz->addActionListener(cpuSpeedButtonActionListener);

	opt28Mhz = new gcn::UaeRadioButton("28 Mhz", "radiocpuspeedgroup");
	opt28Mhz->addActionListener(cpuSpeedButtonActionListener);

	optFastest = new gcn::UaeRadioButton("Fastest", "radiocpuspeedgroup");
	optFastest->addActionListener(cpuSpeedButtonActionListener);

	grpCPUSpeed = new gcn::Window("CPU Speed");
	grpCPUSpeed->setPosition(DISTANCE_BORDER + grpCPU->getWidth() + DISTANCE_NEXT_X, DISTANCE_BORDER);
	grpCPUSpeed->add(opt7Mhz,  5, 10);
	grpCPUSpeed->add(opt14Mhz, 5, 40);
	grpCPUSpeed->add(opt28Mhz, 5, 70);
	grpCPUSpeed->add(optFastest, 5, 100);
	grpCPUSpeed->setMovable(false);
	grpCPUSpeed->setSize(95, 145);
  grpCPUSpeed->setBaseColor(gui_baseCol);

  category.panel->add(grpCPUSpeed);

  RefreshPanelCPU();
}


void ExitPanelCPU(void)
{
  delete optCPU68000;
  delete optCPU68010;
  delete optCPU68EC020;
  delete optCPU68020;
  delete optCPU68040;
  delete chkCPUCompatible;
  delete chkJIT;
  delete grpCPU;
  delete cpuButtonActionListener;
  delete cpuCompActionListener;
  delete jitActionListener;

  delete optFPUnone;
  delete optFPU68881;
  delete optFPU68882;
  delete grpFPU;
  delete fpuButtonActionListener;
  
  delete opt7Mhz;
  delete opt14Mhz;
  delete opt28Mhz;
  delete optFastest;
  delete grpCPUSpeed;
  delete cpuSpeedButtonActionListener;
}


void RefreshPanelCPU(void)
{
  if(changed_prefs.address_space_24)
  {
    if(changed_prefs.cpu_level == 0)
      optCPU68000->setSelected(true);
    else if(changed_prefs.cpu_level == 1)
      optCPU68010->setSelected(true);
    else if(changed_prefs.cpu_level == 2)
      optCPU68EC020->setSelected(true);
  }
  else
  {
    if(changed_prefs.cpu_level == 2 || changed_prefs.cpu_level == 3)
      optCPU68020->setSelected(true);
    else if(changed_prefs.cpu_level == 4)
      optCPU68040->setSelected(true);
  }

  chkCPUCompatible->setSelected(changed_prefs.cpu_compatible > 0);
  chkCPUCompatible->setEnabled(changed_prefs.cpu_level == 0);
  chkJIT->setSelected(changed_prefs.cachesize > 0);

  if(changed_prefs.cpu_level <= 2)
    optFPUnone->setSelected(true);
  else
    optFPU68881->setSelected(true);
  
	if (changed_prefs.m68k_speed == M68K_SPEED_7MHZ_CYCLES)
    opt7Mhz->setSelected(true);
  else if (changed_prefs.m68k_speed == M68K_SPEED_14MHZ_CYCLES)
    opt14Mhz->setSelected(true);
  else if (changed_prefs.m68k_speed == M68K_SPEED_25MHZ_CYCLES)
    opt28Mhz->setSelected(true);
  else if (changed_prefs.m68k_speed == -1)
    optFastest->setSelected(true);
}
