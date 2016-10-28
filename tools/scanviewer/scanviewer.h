/**
 * Scan viewer
 * @author tweber
 * @date mar-2015
 * @license GPLv2
 */

#ifndef __TAZ_SCANVIEWER_H__
#define __TAZ_SCANVIEWER_H__

#include <QDialog>
#include <QSettings>
#include <string>
#include <vector>
#include <memory>

#include "tlibs/file/loadinstr.h"
#include "libs/qthelper.h"
#include "libs/globals.h"
#include "ui/ui_scanviewer.h"
#include "FitParamDlg.h"


class ScanViewerDlg : public QDialog, Ui::ScanViewerDlg
{ Q_OBJECT
protected:
	QSettings m_settings;
	std::string m_strCurDir, m_strCurFile;
	std::string m_strSelectedKey;
	std::vector<std::string> m_vecExts;

	bool m_bDoUpdate = 0;
	tl::FileInstrBase<t_real_glob> *m_pInstr = nullptr;
	std::vector<t_real_glob> m_vecX, m_vecY;
	std::vector<t_real_glob> m_vecFitX, m_vecFitY;
	std::unique_ptr<QwtPlotWrapper> m_plotwrap;
	std::string m_strX, m_strY, m_strCmd;

	FitParamDlg *m_pFitParamDlg = nullptr;

protected:
	void ClearPlot();
	void PlotScan();
	void ShowProps();

	void GenerateForRoot();
	void GenerateForGnuplot();
	void GenerateForPython();
	void GenerateForHermelin();

	virtual void closeEvent(QCloseEvent* pEvt) override;

#ifndef NO_FIT
	template<std::size_t iNumArgs, class t_func>
	bool Fit(t_func&& func,
		const std::vector<std::string>& vecParamNames,
		std::vector<t_real_glob>& vecVals,
		std::vector<t_real_glob>& vecErrs,
		const std::vector<bool>& vecFixed);
#endif

protected slots:
	void GenerateExternal(int iLang=0);

	void UpdateFileList();
	void FileSelected(QListWidgetItem *pItem, QListWidgetItem *pItemPrev);
	void PropSelected(QTableWidgetItem *pItem, QTableWidgetItem *pItemPrev);
	void SelectDir();
	void ChangedPath();

	void XAxisSelected(const QString&);
	void YAxisSelected(const QString&);

	void ShowFitParams();
	void FitGauss();
	void FitLorentz();
	void FitVoigt();

	//void openExternally();

public:
	ScanViewerDlg(QWidget* pParent = nullptr);
	virtual ~ScanViewerDlg();
};


#endif