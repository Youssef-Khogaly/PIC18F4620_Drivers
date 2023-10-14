/* 
 * File:   SPI_cfg.h
 * Author: yosse
 *
 * Created on October 4, 2023, 2:14 AM
 */

#ifndef SPI_CFG_H
#define	SPI_CFG_H



#define SPI_SLAVE_MODE      0
#define SPI_MASTER_MODE     1


#define SPI_SS_DISABLE      0
#define SPI_SS_ENABLE       1

/*
 * options:
 *          SPI_SLAVE_MODE
 *          SPI_MASTER_MODE
 */
#define SPI_MODE        SPI_MASTER_MODE

/*
 options:
 *         SPI_SS_DISABLE
 *         SPI_SS_ENABLE
 */
#define SPI_SS_MODE        SPI_SS_ENABLE


#if SPI_MODE == SPI_MASTER_MODE && SPI_SS_MODE == SPI_SS_ENABLE


#define SPI_NUMBER_OF_SLAVES        1

#endif

#endif	/* SPI_CFG_H */

